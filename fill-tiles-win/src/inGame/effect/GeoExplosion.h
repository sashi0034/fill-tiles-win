//
// Created by sashi0034 on 2022/08/04.
//

#ifndef FILL_TILES_GEOEXPLOSION_H
#define FILL_TILES_GEOEXPLOSION_H

#include "../MainScene.h"
#include "../EffectManager.h"

namespace inGame::effect
{

    class GeoExplosion : public ActorBase
    {
    public:
        static void Produce(EffectManager *effectManager, const Vec2<double> &pos);

        void Update(IAppState *appState) override;
    private:
        GeoExplosion(EffectManager *effectManager, const Vec2<double> &pos);
        EffectManager* m_Manager;
        double m_Lifetime{};
        static const inline int cellSize = 24;

        static CoroTask produceEffectAsync(CoroTaskYield& yield, EffectManager *manager, const Vec2<double> pos);

        SpriteTexture m_Texture = SpriteTexture::Create();
    };

} // inGame

#endif //FILL_TILES_GEOEXPLOSION_H
