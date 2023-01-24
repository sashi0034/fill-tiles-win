//
// Created by sashi0034 on 2022/08/12.
//

#ifndef FILL_TILES_TEXTURESCRAPPING_H
#define FILL_TILES_TEXTURESCRAPPING_H

#include "../MainScene.h"
#include "../EffectManager.h"

namespace inGame::effect
{
    struct TextureScrappingArgs
    {
    public:
        EffectManager* const EffectManagerRef;
        Vec2<double> Pos;
        Rect<int> SrcRect;
        Graph* const SrcGraph;
        const int ScrapSize = 8;
    };

    class TextureScrapping : public ActorBase
    {
        static inline const std::string className = "TextureScrapping";
    public:
        static void Produce(const TextureScrappingArgs &args);

        void Update(IAppState *appState) override;
    private:
        TextureScrapping(EffectManager *effectManager, Graph *const srcGraph, const Rect<int> &srcRect, const Vec2<double> &pos, const Vec2<double>& velocity);
        static void produceEffectAsync(CoroTaskYield &yield, TextureScrappingArgs args);
        EffectManager* m_Manager;
        double m_Lifetime{};
        Vec2<double> m_Pos{};
        Vec2<double> m_Vel{};
        double m_Gravity{};
        double m_MaxLifetime;

        SpriteTexture m_Texture = SpriteTexture::Create();
    };

} // inGame

#endif //FILL_TILES_TEXTURESCRAPPING_H
