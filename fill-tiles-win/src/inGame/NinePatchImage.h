//
// Created by sashi0034 on 2022/07/03.
//

#ifndef FILL_TILES_NINEPATCHIMAGE_H
#define FILL_TILES_NINEPATCHIMAGE_H

#include "../gameEngine/gameEngine.h"

namespace inGame
{
    class NinePatchImage
    {
    public:
        NinePatchImage(IAppState *app, Graph *srcGraph, const Vec2<double> &centerPos, const Vec2<double> &sizeByUnit,
                       const Vec2<double> &sideRatio);
        void SetSize(const Vec2<double>& sizeByUnit);
        SpriteTexture& GetSprite();
    private:
        IAppState* m_App;
        SpriteTexture m_Sprite = SpriteTexture::Create();
        Graph* m_SrcGraph;
        unique_ptr<Graph> m_RenderingGraph{};

        Vec2<double> m_CenterPos;
        Vec2<double> m_SideRatio;
        Vec2<int> m_RenderingSize;
        Vec2<int> m_SrcGraphDividePoint[4]{};
        Vec2<int> m_RenderingGraphDividePoint[4]{};

        void renderNinePath();

        void renderUnsafely(SDL_Renderer *renderer, SDL_Texture *renderingTarget) const;
    };
}


#endif //FILL_TILES_NINEPATCHIMAGE_H
