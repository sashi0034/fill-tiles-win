//
// Created by sashi0034 on 2022/08/10.
//

#include "SteppedOnMineEvent.h"
#include "MainScene.h"
#include "character/MineFlower.h"
#include "effect/GeoExplosion.h"
#include "Player.h"


namespace inGame
{

    IFieldManager *SteppedOnMineEventArgs::GetFieldManager() const
    {
        return MainScene->GetFieldManager();
    }

    void SteppedOnMineEvent::StartEvent(const SteppedOnMineEventArgs &args)
    {
        args.GetFieldManager()->GetCoroutine()->Start([args, this](auto&& yield){ performExplosionAsync(yield, args); });
    }

    void SteppedOnMineEvent::performExplosionAsync(CoroTaskYield &yield, SteppedOnMineEventArgs args)
    {
        auto eventInScope = args.MainScene->GetFieldEventManager()->UseEvent();
        eventInScope.StartFromHere();

        LOG_INFO << "stepped on mine." << std::endl;

        args.GetFieldManager()->GetCoroutine()->Start([this, &args](auto&& yield){explodeFlowersAsync(yield, args); });

        args.MainScene->GetPlayer()->ChangeStateToDead();

        coroUtil::WaitForTime(yield, 3.0);

        args.MainScene->ToSuper()->RequestResetScene(MainSceneResetInfo::FromLevel(args.ClassAtFailed->GetClassLevel()));
    }

    // 順番に爆発していく演出
    void SteppedOnMineEvent::explodeFlowersAsync(CoroTaskYield &yield, SteppedOnMineEventArgs args)
    {
        auto const bloomedList = args.ClassAtFailed->SortBloomedListByPos(args.SteppedPos)->GetBloomedList();

        for (int i=0; i<int(bloomedList.size()); ++i)
        {
            auto targetFlower = bloomedList[i];

            effect::GeoExplosion::Produce(
                    args.MainScene->GetEffectManager(),
                    targetFlower->Position.GetVecByFiledPixel() + FieldManager::MatPixelSize.CastTo<double>() / 2.0);

            targetFlower->Destroy();

            coroUtil::WaitForTime(yield, 0.1);
        }
    }

} // inGame