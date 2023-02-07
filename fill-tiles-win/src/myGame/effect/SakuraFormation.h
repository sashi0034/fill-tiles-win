//
// Created by sashi0034 on 2022/08/11.
//

#ifndef FILL_TILES_SAKURAFORMATION_H
#define FILL_TILES_SAKURAFORMATION_H

#include "../MainScene.h"
#include "../EffectManager.h"

namespace myGame::effect
{

    class SakuraFormation : public ActorBase
    {
        static const inline std::string className = "SakuraFormation";
    public:
        static void Produce(EffectManager *effectManager, const Vec2<double> &pos);

        void Update(IAppState *appState) override;
    private:
        SakuraFormation(EffectManager *effectManager, const Vec2<double> &pos, int kind);
        EffectManager* m_Manager;
        double m_Lifetime{};
        static const inline int cellSize = 32;

        static CoroTask produceEffectAsync(CoroTaskYield& yield, EffectManager *manager, const Vec2<double> pos);

        SpriteTexture m_Texture = SpriteTexture::Create();
    };

} // myGame

#endif //FILL_TILES_SAKURAFORMATION_H
