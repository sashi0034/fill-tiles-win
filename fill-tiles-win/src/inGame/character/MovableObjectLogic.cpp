//
// Created by sashi0034 on 2022/08/13.
//

#include "MovableObjectLogic.h"

namespace inGame
{
    bool character::MovableObjectLogic::CanMove(EAngle angle)
    {
        auto field =mainScene->GetFieldManager();
        const auto currPos = view->GetMatPos();

        return field->CanMovableObjectMoveTo(currPos, angle);
    }

    void character::MovableObjectLogic::ForceMove(EAngle angle)
    {
        LOG_ASSERT(CanMove(angle), "invalid move");
        
        mainScene->GetFieldManager()->GetCoroutine()->Start(
                new CoroTaskCall([&](auto&& yield){ move(yield, angle);}));
    }

    void character::MovableObjectLogic::move(CoroTaskYield &yield, EAngle angle)
    {
        auto eventInScope = mainScene->GetFieldEventManager()->UseEvent();
        eventInScope.StartFromHere();

        yield();

        constexpr double duration = 0.6;
        auto animation = mainScene->GetFieldManager()->GetAnimator()->TargetTo(view->GetModel())
                ->AnimPosition(Angle(angle).ToXY().CastTo<double>() * FieldManager::PixelPerMat, duration)->SetRelative(true)
                ->SetEase(EAnimEase::OutBack)
                ->ToWeakPtr();

        coroUtil::WaitForExpire(yield, animation);
    }

    character::MovableObjectLogic::MovableObjectLogic(MainScene *mainScene, CharacterViewModel *view) : mainScene(mainScene),
                                                                                                         view(view)
    {}
} // inGame