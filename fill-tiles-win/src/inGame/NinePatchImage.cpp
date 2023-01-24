//
// Created by sashi0034 on 2022/07/03.
//

#include "NinePatchImage.h"

#include <memory>
#include "ZIndex.h"

namespace inGame
{
    NinePatchImage::NinePatchImage(IAppState *app, Graph *srcGraph, const Vec2<double> &centerPos,
                                   const Vec2<double> &sizeByUnit,
                                   const Vec2<double> &sideRatio)
     : m_App(app), m_SrcGraph(srcGraph), m_CenterPos(centerPos), m_SideRatio(sideRatio)
    {
        const auto srcSize = srcGraph->GetSize();
        m_SrcGraphDividePoint[0] = Vec2{0, 0};
        m_SrcGraphDividePoint[1] = Vec2{int(sideRatio.X * srcSize.X), int(sideRatio.Y * srcSize.Y)};
        m_SrcGraphDividePoint[2] = Vec2{int((1 - sideRatio.X) * srcSize.X), int((1 - sideRatio.Y) * srcSize.Y)};
        m_SrcGraphDividePoint[3] = srcSize;

        SetSize(sizeByUnit);

        m_Sprite.SetRenderingProcess(std::bind(renderingProcess::RenderSpriteDotByDot, std::placeholders::_1, &m_Sprite));
        ZIndexUi(&m_Sprite).SetIndex(0).ApplyZ();
    }

    void NinePatchImage::SetSize(const Vec2<double> &sizeByUnit)
    {
        m_RenderingSize = (sizeByUnit * m_App->GetPixelPerUnit()).CastTo<int>();
        const auto sprPos = (m_CenterPos - sizeByUnit / 2.0);
        const int connerLength = (std::min)(m_RenderingSize.X * m_SideRatio.X, m_RenderingSize.Y * m_SideRatio.Y);

        m_RenderingGraphDividePoint[0] = Vec2{0, 0};
        m_RenderingGraphDividePoint[1] = Vec2{connerLength, connerLength};
        m_RenderingGraphDividePoint[2] = m_RenderingSize - m_RenderingGraphDividePoint[1];
        m_RenderingGraphDividePoint[3] = m_RenderingSize;

        renderNinePath();

        m_Sprite.SetGraph(m_RenderingGraph.get());
        m_Sprite.SetSrcRect(Rect{Vec2{0, 0}, m_RenderingSize});
        m_Sprite.SetPosition(sprPos);
    }

    void NinePatchImage::renderNinePath()
    {
        auto renderer = m_App->GetRenderer();
        assert(m_RenderingSize.X * m_RenderingSize.Y > 0);
        SDL_Texture *renderingTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                                   SDL_TEXTUREACCESS_TARGET, m_RenderingSize.X, m_RenderingSize.Y);
        renderUnsafely(renderer, renderingTarget);

        m_RenderingGraph = std::make_unique<Graph>(renderingTarget);
    }

    void NinePatchImage::renderUnsafely(SDL_Renderer *renderer, SDL_Texture *renderingTarget) const
    {
        auto renderChange = TempRenderTargetChanger(renderer);
        renderChange.ChangeInScope(renderingTarget)->RenderClear();

        for (int x=0; x<3; ++x)
        {
            for (int y=0; y<3; ++y)
            {
                const auto dividedSrcStart = Vec2{m_SrcGraphDividePoint[x].X, m_SrcGraphDividePoint[y].Y};
                const auto dividedSrcSize =
                        Vec2{m_SrcGraphDividePoint[x + 1].X, m_SrcGraphDividePoint[y + 1].Y} - dividedSrcStart;

                const auto renderingStart = Vec2{m_RenderingGraphDividePoint[x].X, m_RenderingGraphDividePoint[y].Y};
                const auto renderingSrcSize =
                        Vec2{m_RenderingGraphDividePoint[x + 1].X, m_RenderingGraphDividePoint[y + 1].Y} - renderingStart;

                const auto srcRect = SDL_Rect{dividedSrcStart.X, dividedSrcStart.Y, dividedSrcSize.X, dividedSrcSize.Y};
                const auto destRect =SDL_Rect{renderingStart.X, renderingStart.Y, renderingSrcSize.X, renderingSrcSize.Y};

                SDL_RenderCopy(renderer, m_SrcGraph->GetSdlTexture(), &srcRect, &destRect);
            }
        }
    }

    SpriteTexture &NinePatchImage::GetSprite()
    {
        return m_Sprite;
    }
}