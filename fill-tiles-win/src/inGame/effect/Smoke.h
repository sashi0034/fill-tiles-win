//
// Created by sashi0034 on 2022/07/05.
//

#ifndef FILL_TILES_SMOKE_H
#define FILL_TILES_SMOKE_H

#include "../MainScene.h"
#include "../EffectManager.h"

namespace inGame::effect
{
    class Smoke final : public ActorBase
    {
    public:
        static void Produce(EffectManager *effectManager, const Vec2<double> &pos);

        void Update(IAppState *appState) override;
    private:
        double m_LifeTime{};
        Vec2<double> m_Vel;
        static constexpr int initialAlpha = 160;

        Smoke(EffectManager *effectManager, const Vec2<double> &pos, const Vec2<double> &velocity,
              double rotationDeg);
        EffectManager* m_Manager;
        SpriteTexture m_Texture = SpriteTexture::Create();
        static CoroTask produceWithRotating(CoroTaskYield& yield, EffectManager *manager, const Vec2<double> &pos);

        bool passLifeTime(const IAppState *appState);

        static int getCorrectedDeg(const int deg);
    };
}


#endif //FILL_TILES_SMOKE_H
