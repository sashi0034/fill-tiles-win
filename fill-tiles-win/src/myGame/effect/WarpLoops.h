//
// Created by sashi0034 on 2022/08/21.
//

#ifndef FILL_TILES_WARPLOOPS_H
#define FILL_TILES_WARPLOOPS_H


#include "../MainScene.h"
#include "../EffectManager.h"

namespace myGame::effect
{

    class WarpLoops: public ActorBase
    {
        static const inline std::string className = "WarpLoops";
    public:
        static void Produce(EffectManager *effectManager, const Vec2<double> &pos);

        void Update(IAppState *appState) override;
    private:
        WarpLoops(EffectManager *effectManager, const Vec2<double> &pos);
        EffectManager* m_Manager;
        double m_Lifetime{};
        const Vec2<double> initialPos;
        static const inline int cellSize = 16;

        static CoroTask produceEffectAsync(CoroTaskYield& yield, EffectManager *manager, const Vec2<double> pos);

        SpriteTexture m_Texture = SpriteTexture::Create();
    };

} // myGame

#endif //FILL_TILES_WARPLOOPS_H
