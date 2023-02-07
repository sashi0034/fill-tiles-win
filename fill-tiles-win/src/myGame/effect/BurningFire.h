//
// Created by sashi0034 on 2022/08/03.
//

#ifndef FILL_TILES_BURNINGFIRE_H
#define FILL_TILES_BURNINGFIRE_H

#include "../MainScene.h"
#include "../EffectManager.h"


namespace myGame::effect
{
    class BurningFire final : public ActorBase
    {
    public:
        static void Produce(EffectManager *effectManager, const Vec2<double> &pos);

        void Update(IAppState *appState) override;
    private:
        BurningFire(EffectManager *effectManager, const Vec2<double> &pos);
        static CoroTask produceEffectsAsync();
        EffectManager* m_Manager;
        double m_Lifetime{};
        static const inline int cellSize = 192;

        SpriteTexture m_Texture = SpriteTexture::Create();
    };
}


#endif //FILL_TILES_BURNINGFIRE_H
