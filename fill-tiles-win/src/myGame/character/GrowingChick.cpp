//
// Created by sashi0034 on 2022/08/17.
//

#include "GrowingChick.h"
#include "../Player.h"
#include "../ZIndex.h"
#include "../effect/TextureScrapping.h"

namespace myGame::character
{
    using growth = EGrowingChickGrowth;

    const int pixelPerMat = FieldManager::PixelPerMat;

    GrowingChick::GrowingChick(MainScene *mainScene, const MatPos &matPos)
            : CharacterBase(mainScene->GetFieldManager()),
              m_Scene(mainScene),
              m_View(mainScene->GetScrollManager(), mainScene->GetRoot()->RscImage->egg_16x16.get())
    {

        m_View.SetModelPos(matPos);

        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, childCellSrcSize});

        setViewPos(eggCellSrcSize);

        m_View.SetCollider(this, mainScene->GetFieldManager(),
                           Rect{0, 0, FieldManager::PixelPerMat, FieldManager::PixelPerMat});

        animWhenEgg();

        if (auto player = mainScene->GetPlayer())
        {
            subscribePlayerMove(mainScene, player);
        }
    }

    unique_ptr<TextPassage> GrowingChick::createManualText(MainScene *mainScene) const
    { return std::make_unique<TextPassage>(
            mainScene->GetRoot()->GetAppState(), mainScene->GetRoot()->RscFont->KHDotAkihabara32px.get(),
            Rgba(255, 255, 255),
            Rgba(16, 16, 16)); }

    void GrowingChick::setViewPos(const Vec2<int>& cellSize)
    {
        m_View.GetView().SetPosition(
                FieldManager::CharacterPadding -
                Vec2<double>{(cellSize.X - pixelPerMat) / 2.0, double(cellSize.Y - pixelPerMat)});
    }

    void GrowingChick::animWhenEgg()
    {
        constexpr double duration = 0.2;
        m_AnimationRef = animator->TargetTo(m_View.GetView())
                ->AnimGraph(childCellSrcSize)->SetFrameLoopEndless(true)
                ->AddFrame(Vec2{0, 0}, duration * 4)
                ->AddFrame(Vec2{1, 0}, duration)
                ->AddFrame(Vec2{2, 0}, duration)
                ->AddFrame(Vec2{3, 0}, duration)
                ->ToWeakPtr();
    }

    void GrowingChick::Update(IAppState*)
    {
        ZIndexCharacter(m_View).ApplyZ();
    }

    void GrowingChick::subscribePlayerMove(MainScene *mainScene, const Player *player)
    {
        player->OnMoveFinish().subscribe([mainScene, this](PlayerMoveData* moveData){
            if (m_Growth!=growth::Egg) return;

            constexpr double nearDistance = 1;
            if (moveData->AfterPos.CalcManhattan(m_View.GetMatPos())>nearDistance) return;
            mainScene->GetFieldManager()->GetCoroutine()->Start([this](auto&& yield){
                startYoungProcess(yield);
            });
        });
    }

    // イベント発生時の一連の処理
    void GrowingChick::startYoungProcess(CoroTaskYield &yield)
    {
        auto eventInScope = m_Scene->GetFieldEventManager()->AwaitIfEventExist(yield)->UseEvent();
        eventInScope.StartFromHere();

        auto manualText = createManualText(m_Scene);
        initManualText(manualText);

        // 説明テキストアニメ
        auto&& animator = m_Scene->GetTextureAnimator();
        auto&& textAnimStart = animator.TargetVirtual()
            ->AnimValue(0, 1, [this, &manualText](double value) {
                manualText->SetScale(VecDouble2{ value, 1 });
                manualText->UpdateView();
            }, 0.3)->SetEase(EAnimEase::OutBack)->ToWeakPtr();

        becomeYoung();

        auto const scroll = m_Scene->GetPlayer()->GetScroll();
        scroll->ChangeFocus(&m_View.GetModel());

        performAnimJumpUpWhenBorn(yield);

        moveUntilConfirm(yield);
        animator.Destroy(textAnimStart);

        scroll->ResetFocus();

        becomeAdult();

        // 説明テキストアニメ
        auto&& textAnimEnd = animator.TargetVirtual()
            ->AnimValue(1, 0, [this, &manualText](double value) {
                manualText->SetScale(VecDouble2{ value, 1 });
                manualText->UpdateView();
            }, 0.3)->SetEase(EAnimEase::InBack)->ToWeakPtr();
        coroUtil::WaitForExpire(yield, textAnimEnd);
    }

    void GrowingChick::initManualText(unique_ptr<TextPassage> &manualText)
    {
        manualText->SetZIndex(10);
        manualText->SetAlignment(ETextHorizontalAlign::Center, ETextVerticalAlign::Center);
        manualText->SetPositionParent(m_Scene->GetRoot()->GetAnchor()->GetOf(ENineAnchorX::Center, ENineAnchorY::Bottom));

        double margin = lua->GetState()[className]["ManualTextMargin"];
        manualText->SetPos(Vec2<double>{0, -margin});

        std::string content = lua->GetState()[className]["ManualTextContent"];
        manualText->UpdateTextAndView(content);
    }

    void GrowingChick::performAnimJumpUpWhenBorn(CoroTaskYield &yield)
    {
        // 生まれて飛び跳ねる
        ParabolaAnimation::Create(m_Scene->GetEffectManager(), &m_View.GetView())
            ->SetSpeedByPeekHeightAndTime(8, 0.2)
            ->AwaitForReturnToStart(yield)
            ->Forget();
        ParabolaAnimation::Create(m_Scene->GetEffectManager(), &m_View.GetView())
                ->SetSpeedByPeekHeightAndTime(4, 0.2)
                ->AwaitForReturnToStart(yield)
                ->Forget();
    }

    void GrowingChick::becomeYoung()
    {
        m_Growth = growth::Child;

        // 卵の殻を割る演出
        effect::TextureScrapping::Produce(effect::TextureScrappingArgs{
                m_Scene->GetEffectManager(),
                m_View.GetViewModelPos(),
                m_View.GetView().GetSrcRect(),
                m_View.GetView().GetGraph(),
                8});

        m_View.GetView().SetGraph(m_Scene->GetRoot()->RscImage->chick_16x16.get());
        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, childCellSrcSize});
        setViewPos(childCellSrcSize);
        animWaitWhenChild(EAngle::Down);
    }

    void GrowingChick::moveUntilConfirm(CoroTaskYield &yield)
    {
        while (true)
        {
            yield();

            const auto keyState = appState->GetKeyboardState();

            // 終了ボタンを押したかチェック
            const bool isConfirm = input::IsPushingConfirm(keyState);
            if (isConfirm) break;

            // お花を全部そろえたので終了
            auto&& mineFlowerManager = m_Scene->GetFieldManager()->GetMineFlowerManager();
            if (mineFlowerManager->GetCurrMineFlowerClass() == nullptr || mineFlowerManager->GetCurrMineFlowerClass()->HasMineFlower() == false) break;

            auto inputAngle = input::GetInputAngle(keyState);

            // 入力があるまで待機
            if (inputAngle==EAngle::None) continue;

            bool hasMoved = tryMoveByAngleSync(yield, inputAngle,
                                              [inputAngle, this]() { animMoveWhenChild(inputAngle); });
            if (!hasMoved) continue;

            // 押されてる間歩き続ける
            while (true)
            {
                bool hasMovedAgain = moveIfNewInputIsSameOfBefore(yield, &inputAngle);
                if (!hasMovedAgain) break;
            }

            animWaitWhenChild(inputAngle);
        }
    }

    bool GrowingChick::moveIfNewInputIsSameOfBefore(CoroTaskYield &yield, EAngle *inputAngle)
    {
        EAngle newInputAngle = input::GetInputAngle(appState->GetKeyboardState());
        if (newInputAngle==EAngle::None) return false;

        // 画像をまた反転させる必要があるなら移動しない
        if (isFlipViewByAngle(*inputAngle) != isFlipViewByAngle(newInputAngle)) return false;

        *inputAngle = newInputAngle;
        bool hasMoved = tryMoveByAngleSync(yield, *inputAngle, [](){});
        if (!hasMoved) return false;

        return true;
    }

    bool GrowingChick::tryMoveByAngleSync(CoroTaskYield &yield, EAngle inputAngle, const std::function<void()>& onStartAnim)
    {
        auto const field = m_Scene->GetFieldManager();

        if (!field->CheckMoveTo(m_View.GetMatPos(), inputAngle).CanMove) return false;

        onStartAnim();

        constexpr double moveTime = 0.3;
        auto moveAnim = animator->TargetTo(m_View.GetModel())
                ->AnimPosition(Angle(inputAngle).ToXY().CastTo<double>() * pixelPerMat, moveTime)->SetRelative(true)
                ->ToWeakPtr();

        coroUtil::WaitForExpire(yield, moveAnim);

        field->GetMineFlowerManager()->CheckStepOnMine(m_View.GetMatPos());

        return true;
    }

    void GrowingChick::animWaitWhenChild(EAngle angle)
    {
        constexpr double duration = 0.2;
        animator->Destroy(m_AnimationRef);
        m_AnimationRef = animator->TargetTo(m_View.GetView())
                ->AnimGraph(childCellSrcSize)->SetFrameLoopEndless(true)->SetCanFlip(false)
                ->AddFrame(Vec2{0, 0}, duration)
                ->AddFrame(Vec2{1, 0}, duration)
                ->AddFrame(Vec2{2, 0}, duration)
                ->ToWeakPtr();

        flipViewByAngle(angle);
    }

    void GrowingChick::flipViewByAngle(const EAngle &angle)
    { m_View.GetView().SetFlip(isFlipViewByAngle(angle)); }

    bool GrowingChick::isFlipViewByAngle(const EAngle &angle) const
    { return (angle == EAngle::Left || angle == EAngle::Down); }

    void GrowingChick::animMoveWhenChild(EAngle angle)
    {
        constexpr double duration = 0.2;
        animator->Destroy(m_AnimationRef);
        m_AnimationRef = animator->TargetTo(m_View.GetView())
                ->AnimGraph(childCellSrcSize)->SetFrameLoopEndless(true)->SetCanFlip(false)
                ->AddFrame(Vec2{0, 1}, duration)
                ->AddFrame(Vec2{1, 1}, duration)
                ->AddFrame(Vec2{2, 1}, duration)
                ->AddFrame(Vec2{3, 1}, duration)
                ->ToWeakPtr();

        flipViewByAngle(angle);
    }

    void GrowingChick::becomeAdult()
    {
        m_Growth = growth::Adult;

        m_View.GetView().SetGraph(m_Scene->GetRoot()->RscImage->chicken_32x32.get());

        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, adultCellSrcSize});

        setViewPos(adultCellSrcSize);

        constexpr double duration = 0.3;
        animator->Destroy(m_AnimationRef);
        m_AnimationRef = animator->TargetTo(m_View.GetView())
                ->AnimGraph(adultCellSrcSize)->SetFrameLoopEndless(true)->SetCanFlip(false)
                ->AddFrame(Vec2{0, 0}, duration)
                ->AddFrame(Vec2{1, 0}, duration)
                ->AddFrame(Vec2{2, 0}, duration)
                ->ToWeakPtr();
    }


} // myGame
