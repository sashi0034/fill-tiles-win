//
// Created by sashi0034 on 2022/07/18.
//

#include "PuniCat.h"
#include "../ZIndex.h"
#include "../Player.h"

namespace inGame::character
{
    PuniCat::PuniCat(MainScene *mainScene, const MatPos &matPos)
            : CharacterBase(mainScene->GetFieldManager()),
            m_Scene(mainScene),
            m_View(mainScene->GetScrollManager(), mainScene->GetRoot()->RscImage->punicat_24x24.get())
    {
        const int pixelPerMat = FieldManager::PixelPerMat;
        m_View.GetView().SetSrcRect(Rect{Vec2<int>{0, 0}, cellSrcSize});

        m_View.SetModelPos(matPos);

        m_View.GetView().SetPosition(
                FieldManager::CharacterPadding -
                Vec2<double>{(cellSrcSize.X - pixelPerMat) / 2.0, double(cellSrcSize.Y - pixelPerMat)});

        m_View.SetCollider(this, mainScene->GetFieldManager(),
                           Rect{0, 0, FieldManager::PixelPerMat, FieldManager::PixelPerMat});

        animByAngle(EAngle::Down);

        if (auto player = mainScene->GetPlayer())
        {
            subscribePlayerAction(mainScene, player);
        }
    }

    void PuniCat::subscribePlayerAction(MainScene *mainScene, const Player *player)
    {
        player->OnAction().subscribe([&, mainScene, this](auto&& action){
           if (auto actionDetail = dynamic_cast<PlayerActionPushCatfish*>(action))
           {
               auto actedCatfish = actionDetail->TouchedCatfish;
               searchCatfishEveryAngle(mainScene, actedCatfish);
           }
        });
    }

    void PuniCat::searchCatfishEveryAngle(MainScene *mainScene, Catfish *nullableTargetCatfish)
    {
        if (nullableTargetCatfish)
            if (!nullableTargetCatfish->GetEatableFlag().IsUp()) return;

        const auto currPos = m_View.GetMatPos();

        for (auto angle : Angle::EveryAngle)
        {
            constexpr int maxStep = 8;
            // 各方向ごとに進めなくなるまでcatfishがあるかを確認していきます。
            for (int step=0; step<maxStep; ++step)
            {
                const auto stepVec = angle.ToXY();
                const MatPos checkingPos = currPos + MatPos(stepVec * step);
                const auto checking = mainScene->GetFieldManager()->CheckMoveTo(checkingPos, angle.GetKind());

                // どれを食べるか指定あり
                if (nullableTargetCatfish != nullptr)
                {
                    if (checking.CollidedObject == nullableTargetCatfish)
                        startGoToEatCatfish(mainScene, nullableTargetCatfish, stepVec, checkingPos, angle.GetKind());
                }
                // どれを食べるか指定なし
                else
                {
                    if (auto foundCatfish = dynamic_cast<Catfish*>(checking.CollidedObject))
                        startGoToEatCatfish(mainScene, foundCatfish, stepVec, checkingPos, angle.GetKind());
                }
                if (!checking.CanMove) break;
            }
        }
    }

    void PuniCat::startGoToEatCatfish(MainScene *mainScene, Catfish *targetCatfish, const Vec2<int> &stepVec,
                                      const MatPos &checkingPos, EAngle angle)
    {
        targetCatfish->GetEatableFlag().GoDown();
        mainScene->GetFieldManager()->GetCoroutine()->Start(
                new CoroTaskCall([&](auto&& yield){
                    moveToEatFish(yield, targetCatfish, checkingPos + MatPos(stepVec), angle);}));
    }

    void PuniCat::Update(IAppState *)
    {
        ZIndexCharacter(m_View).ApplyZ();
    }

    void PuniCat::moveToEatFish(CoroTaskYield &yield, Catfish *targetFood, const MatPos &goingPos, EAngle angle)
    {
        auto eventInScope = m_Scene->GetFieldEventManager()->UseEvent();
        eventInScope.StartFromHere();

        yield();

        animByAngle(angle);

        // 魚のある目的地まで1歩ずつ移動
        while (true)
        {
            const auto currPos = m_View.GetMatPos();

            // 地雷があったら踏んだことにする
            m_Scene->GetFieldManager()->GetMineFlowerManager()->CheckStepOnMine(currPos);

            if (currPos == goingPos) break;

            constexpr double duration = 0.3;
            auto animation = m_Scene->GetFieldManager()->GetAnimator()->TargetTo(m_View.GetModel())
                    ->AnimPosition(Angle(angle).ToXY().CastTo<double>() * FieldManager::PixelPerMat, duration)->SetRelative(true)
                    ->ToWeakPtr();

            coroUtil::WaitForExpire(yield, animation);
        }

        // 魚が跳び跳ねて
        targetFood->JumpWhenEat()->AwaitForReturnToStart(yield)->Forget();

        // 食べて消す
        targetFood->Destroy();

        searchCatfishEveryAngle(m_Scene, nullptr);
    }


    void PuniCat::animByAngle(EAngle angle)
    {
        auto const animator = m_Scene->GetFieldManager()->GetAnimator();

        animator->Destroy(m_AnimationRef);

        auto&& base = animator->TargetTo(m_View.GetView())
                ->AnimGraph(cellSrcSize)->SetFrameLoopEndless(true);

        constexpr double duration = 0.2;
        switch (angle)
        {
            case EAngle::Down:
                m_AnimationRef = base
                    ->AddFrame(Vec2{0, 0}, duration * 1.5)
                    ->AddFrame(Vec2{1, 0}, duration)
                    ->AddFrame(Vec2{2, 0}, duration)
                    ->AddFrame(Vec2{3, 0}, duration)
                    ->ToWeakPtr();
                break;
            case EAngle::Right:
                m_AnimationRef = base
                        ->AddFrame(Vec2{0, 3}, duration * 1.5)
                        ->AddFrame(Vec2{1, 3}, duration)
                        ->AddFrame(Vec2{2, 3}, duration)
                        ->AddFrame(Vec2{3, 3}, duration)
                        ->ToWeakPtr();
                break;
            case EAngle::Up:
                m_AnimationRef = base
                        ->AddFrame(Vec2{0, 2}, duration * 1.5)
                        ->AddFrame(Vec2{1, 2}, duration)
                        ->AddFrame(Vec2{2, 2}, duration)
                        ->AddFrame(Vec2{3, 2}, duration)
                        ->ToWeakPtr();
                break;
            case EAngle::Left:
                m_AnimationRef = base
                        ->AddFrame(Vec2{0, 3}, duration * 1.5)
                        ->AddFrame(Vec2{1, 3}, duration)
                        ->AddFrame(Vec2{2, 3}, duration)
                        ->AddFrame(Vec2{3, 3}, duration)
                        ->ToWeakPtr();
                break;
            default:
                assert(false);
        }

    }
} // inGame
