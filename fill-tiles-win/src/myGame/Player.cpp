//
// Created by sashi0034 on 2022/05/28.
//

#include "Player.h"

#include <memory>
#include "GameRoot.h"
#include "FieldManager.h"
#include "ZIndex.h"
#include "player/PlayerMoveData.h"
#include "character/Catfish.h"
#include "character/SolidRock.h"

using namespace boost::coroutines2;

namespace myGame
{
    Player::Player(IChildrenPool<ActorBase> *belonging, MainScene *mainScene, const MainSceneResetInfo& resetInfo) :
        ActorBase(belonging), m_State(EPlayerState::Walking),
        m_ParentalScene(mainScene),
        m_Field(mainScene->GetFieldManager()),
        m_SteppedCount(resetInfo.PassedStetppedCount)
    {
        m_Image = mainScene->GetRoot()->RscImage->kisaragi_32x32.get();

        initViewModel();

        m_AnimationLogic = std::make_unique<PlayerAnimation>(m_ParentalScene, CellSize, m_PlayerAnimator, m_View.get());

        m_PlayerScroll = std::make_unique<PlayerScroll>(
                    m_ParentalScene->GetFieldEventManager(), m_ParentalScene->GetScrollManager(), &m_View->GetModel());
        
        initAction();
    }

    void Player::initViewModel()
    {
        m_View = std::make_unique<CharacterViewModel>(m_ParentalScene->GetScrollManager(), m_Image);
        m_View->GetView().SetSrcRect(Rect<int>{0, 0, CellSize.X, CellSize.Y});
        const double pixelPerMat = FieldManager::PixelPerMat;
        m_View->GetView().SetPosition(Vec2<double>{
                (pixelPerMat - CellSize.X) / 2.0,
                pixelPerMat - CellSize.Y} + FieldManager::CharacterPadding);
    }



    CoroTask Player::wait(CoroTaskYield &yield, IAppState *appState)
    {
        yield();

        this->m_AnimationLogic->AnimWait(this->m_Angle);

        // フィールド上でイベントが発生していたら待機する
        this->waitFieldEvent(yield);

        EAngle goingAngle = EAngle::None;
        while (goingAngle == EAngle::None)
        {
            goingAngle = this->tryWalkOrActionByInput(yield, appState);

            yield();
        }

        this->changeStateToWalking(PlayerWalkArgs{appState, goingAngle, true, isDashing(appState->GetKeyboardState()), false});
    }

    void Player::waitFieldEvent(CoroTaskYield &yield)
    {
        coroUtil::WaitForTrue(yield, [this](){return !this->isRunningFieldEvent();});
    }

    EAngle Player::tryWalkOrActionByInput(CoroTaskYield &yield, const IAppState *appState)
    {
        EAngle goingAngle = EAngle::None;
        auto keyState = appState->GetKeyboardState();
        auto inputAngle = input::GetInputAngle(keyState);

        if (inputAngle!=EAngle::None)
        {
            auto checkingMove = this->m_Field->CheckMoveTo(this->GetMatPos(), inputAngle);

            if (checkingMove.CanMove)
                goingAngle = inputAngle;
            else if (this->m_Angle != inputAngle)
            {
                this->m_Angle = inputAngle;
                this->m_AnimationLogic->AnimWait(this->m_Angle);
            }

            auto collidedObject = checkingMove.CollidedObject;

            if (auto solidRock = dynamic_cast<character::SolidRock*>(collidedObject))
                checkPushMovableObject(yield, inputAngle, solidRock->GetMovable());

            if (auto catfish = dynamic_cast<character::Catfish*>(collidedObject))
                pushCatfish(yield, inputAngle, catfish);

        }
        return goingAngle;
    }

    void Player::pushCatfish(CoroTaskYield &yield, EAngle &inputAngle, character::Catfish *catfish)
    {
        bool isPushed = checkPushMovableObject(yield, inputAngle, catfish->GetMovable());
        if (!isPushed) return;

        waitFieldEvent(yield);

        PlayerActionPushCatfish action(catfish);
        m_OnAction.get_subscriber().on_next(&action);
        waitFieldEvent(yield);
    }

    bool Player::checkPushMovableObject(CoroTaskYield &yield, EAngle &inputAngle, character::MovableObjectLogic* movable)
    {
        if (!movable->CanMove(inputAngle)) return false;

        tackleToFieldObject(yield, inputAngle, [&](){
            movable->ForceMove(inputAngle);
        });

        return true;
    }



    void Player::Update(IAppState *appState)
    {
        bool actionUpdating = m_State.UpdateAction();
        if (!actionUpdating) initAction();

        m_SubProcess.ProcessEach([&](ProcessTimer& process){process.Update(appState->GetTime().GetDeltaSec()); });

        m_PlayerAnimator.Update(appState->GetTime().GetDeltaSec());


        ZIndexCharacter(*m_View).ApplyZ();

    }

    void Player::initAction()
    {
        IAppState* app = const_cast<IAppState*>(m_ParentalScene->GetRoot()->GetAppState());
        m_State.ChangeState(EPlayerState::Waiting, new CoroTaskCall(
                [&](auto&& yield){this->wait(yield, app); }));
    }

    void Player::ChangeStateToDead()
    {
        IAppState* app = const_cast<IAppState*>(m_ParentalScene->GetRoot()->GetAppState());
        m_State.ChangeState(EPlayerState::Dead, new CoroTaskCall(
                [&](auto&& yield){this->performDead(yield, app); }));
    }

    CoroTask Player::walk(CoroTaskYield &yield, PlayerWalkArgs args)
    {
        yield();

        auto const goingAngle = args.NewAngle;
        auto const appState = args.AppStateRef;
        const bool isDash = args.IsDash;

        auto moveVector = Angle(goingAngle).ToXY().CastTo<double>() * FieldManager::PixelPerMat;
        double movingTime = args.IsDash ? 0.2 : 0.3;

        if (args.CanChangeAnim)
            this->m_AnimationLogic->AnimWalk(goingAngle, args.IsDash ? 0.5 : 1.0);

        this->m_Angle = goingAngle;

        PlayerMoveData moveData(
            this->GetMatPos(),
            this->GetMatPos() +  MatPos(Angle(this->m_Angle).ToXY()),
            this->m_Angle,
            isDash);

        // 移動開始時のフィールドイベントを発火
        this->m_OnMoveBegin.get_subscriber().on_next(&moveData);

        // 歩行アニメーション
        auto moveAnim = this->m_PlayerAnimator.TargetTo(this->m_View->GetModel())
                ->AnimPosition(moveVector, movingTime)->SetEase(EAnimEase::Linear)->SetRelative(true)
                ->ToWeakPtr();

        coroUtil::WaitForExpire<>(yield, moveAnim);

        m_SteppedCount++;

        // 移動終了時のフィールドイベントを発火
        this->m_OnMoveFinish.get_subscriber().on_next(&moveData);

        // フィールドイベントが発生したら待機にする
        if (this->isRunningFieldEvent()) return;

        //LOG_INFO << "Moved: " << this->GetMatPos().ToString() << std::endl;

        const bool canMoveToNext = this->m_Field->CheckMoveTo(this->GetMatPos(), goingAngle).CanMove;
        if (!canMoveToNext) return;

        // 氷の床
        if (m_Field->GetTileMap()->GetElementAt(this->GetMatPos().GetVec())->IsIceFloor())
        {
            if (!args.IsFromOnIce) this->m_AnimationLogic->AnimWait(goingAngle);
            changeStateToWalking(PlayerWalkArgs{appState, goingAngle, false, false, true});
            return;
        }

        // 引き続き歩行
        if (input::GetInputAngle(appState->GetKeyboardState()) == this->m_Angle && isDash == isDashing(appState->GetKeyboardState()))
        {
            bool canRestartChangeAnim = args.IsFromOnIce;
            changeStateToWalking(PlayerWalkArgs{appState, goingAngle, canRestartChangeAnim, isDash, false});
            return;
        }

    }

    Vec2<double> Player::GetPos()
    {
        return m_View->GetModel().GetPosition();
    }

    void Player::SetPos(const Vec2<double> &pos)
    {
        LOG_INFO << "Player Position set to " << pos.ToString();
        m_View->GetModel().SetPosition(pos);
        m_PlayerScroll->RequestResetScroll();
    }

    void Player::setPos(Vec2<double> newPos)
    {
        m_View->GetModel().SetPosition(newPos);
    }

    bool Player::isDashing(const Uint8 *keyState)
    {
        const auto dashKey = SDL_Scancode ::SDL_SCANCODE_LSHIFT;
        return keyState[dashKey];
    }

    void Player::changeStateToWalking(const PlayerWalkArgs& args)
    {
        m_State.ChangeState(EPlayerState::Walking,
                                  new CoroTaskCall([this, args](auto&& yield) {
                                      walk(std::forward<decltype(yield)>(yield), args); }));
    }

    MatPos Player::GetMatPos()
    {
        auto pixelPos = GetPos().CastTo<int>();
        return MatPos((pixelPos + FieldManager::MatPixelSize / 2) / FieldManager::PixelPerMat);
    }

    rx::observable<PlayerMoveData *> Player::OnMoveBegin() const
    {
        return m_OnMoveBegin.get_observable();
    }

    rx::observable<PlayerMoveData*> Player::OnMoveFinish() const
    {
        return m_OnMoveFinish.get_observable();
    }


    bool Player::isRunningFieldEvent()
    { return m_ParentalScene->GetFieldEventManager()->IsRunning(); }


    void Player::Init()
    {
        constexpr double fps60 = 1.0 / 60;

        m_SubProcess.Birth(new ProcessTimer([&]() {
            m_PlayerScroll->UpdateFixedly();
            return EProcessStatus::Running;
        }, fps60));

    }

    rx::observable<PlayerActionData *> Player::OnAction() const
    {
        return m_OnAction.get_observable();
    }

    void Player::tackleToFieldObject(CoroTaskYield &yield, EAngle angle, const std::function<void()> &onTackleHit)
    {
        const auto&& beforePosition = m_View->GetView().GetPosition();
        const double movePixelByTackling = FieldManager::PixelPerMat * 0.5;
        constexpr double tacklingDuration = 0.2;
        constexpr double endTacklingDuration = 0.2;

        const auto&& tacklingAnimation = m_PlayerAnimator.TargetTo(m_View->GetView())
            ->AnimPosition(Angle(angle).ToXY().CastTo<double>() * movePixelByTackling, tacklingDuration)
            ->SetRelative(true)->SetEase(EAnimEase::InBack)->ToWeakPtr();

        coroUtil::WaitForExpire(yield, tacklingAnimation);

        onTackleHit();

        const auto&& endTacklingAnimation = m_PlayerAnimator.TargetTo(m_View->GetView())
                ->AnimPosition(beforePosition, endTacklingDuration)
                ->SetEase(EAnimEase::InBack)->ToWeakPtr();

        coroUtil::WaitForExpire(yield, endTacklingAnimation);
    }

    CoroTask Player::performDead(CoroTaskYield& yield, IAppState* appState)
    {
        m_AnimationLogic->PerformDead(yield, appState);
    }

    PlayerScroll *Player::GetScroll()
    {
        return m_PlayerScroll.get();
    }

    int Player::GetSteppedCount() const
    {
        return m_SteppedCount;
    }

    void Player::ChangeStateToWarp(const MatPos& startPos, const MatPos& endPos)
    {
        m_State.ChangeState(EPlayerState::Warping,
                            new CoroTaskCall([this, startPos, endPos](auto&& yield) {
                                performWarp(std::forward<decltype(yield)>(yield), startPos, endPos); }));
    }

    CoroTask Player::performWarp(CoroTaskYield &yield, MatPos startPos, MatPos endPos)
    {
        m_AnimationLogic->PerformWarp(yield, startPos, endPos);
    }


}
