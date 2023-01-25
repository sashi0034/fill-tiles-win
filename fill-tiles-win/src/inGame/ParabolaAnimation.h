//
// Created by sashi0034 on 2022/07/25.
//

#ifndef FILL_TILES_PARABOLAANIMATION_H
#define FILL_TILES_PARABOLAANIMATION_H

#include "../gameEngine/gameEngine.h"

#include "EffectManager.h"

namespace inGame
{

    class ParabolaAnimation : public ActorBase
    {
    public:
        static ParabolaAnimation* Create(EffectManager *effectManager, SpriteTexture *target);

        ParabolaAnimation * AwaitForReturnToStart(CoroTaskYield& yield);
        void Forget();

        void Update(IAppState *appState) override;

        ParabolaAnimation * SetSpeedByPeekHeightAndTime(double height, double second);

        void operator=(ParabolaAnimation&) = delete;
    private:
        ParabolaAnimation(EffectManager *effectManager, SpriteTexture *target);
        EffectManager* m_EffectManager;
        WeakPtr<SpriteTexture> m_Target{};
        Vec2<double> m_NormalizedDirection = {0, -1};
        double m_SpeedAccel = -100;
        double m_Speed = 100;
        double m_DeltaMove = 0;

        bool isReturnToStart() const;
    };

} // inGame

#endif //FILL_TILES_PARABOLAANIMATION_H
