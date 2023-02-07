//
// Created by sashi0034 on 2022/05/18.
//

#include "renderingProcess.h"
#include <SDL.h>
#include <SDL_image.h>
#include "iostream"
#include "SpriteTexture.h"

namespace myUtil::renderingProcess
{
    void RenderSprite(IAppState*appState, SpriteTexture *renderingSpr, double baseScale)
    {
        const int pixelPerUnit = appState->GetPixelPerUnit();
        auto renderingGraph = renderingSpr->GetGraph();
        if (renderingGraph == nullptr) return;
        if (!renderingSpr->GetVisible() || !renderingSpr->GetParentalVisibility()) return;

        const auto sprScale = renderingSpr->GetScale();
        auto blend = renderingSpr->GetBlend();
        double rotationDeg = renderingSpr->GetRotationDeg();
        bool isFlip = renderingSpr->GetFlip();
        const auto srcRect = renderingSpr->GetSrcRect();

        auto globalPos = renderingSpr->GetParentalGlobalPosition() + renderingSpr->GetPosition();
        if (sprScale.X != 1)
        {
            std::cout << "";
        }
        Vec2<double> scalingDeltaPos(
                (1.0 - sprScale.X) * srcRect.Width / (double(pixelPerUnit) / baseScale) / 2.0,
                (1.0 - sprScale.Y) * srcRect.Height / (double(pixelPerUnit) / baseScale) / 2.0);
        const Vec2<int> screenPos = ((globalPos + scalingDeltaPos) * pixelPerUnit).CastTo<int>();

        SDL_Renderer *renderer = appState->GetRenderer();


        renderingGraph->RenderGraph(renderer, screenPos, srcRect, sprScale * baseScale, rotationDeg, isFlip, blend);
    }

    void RenderSpriteAlignToUnit(IAppState*appState, SpriteTexture *renderingSpr)
    {
        RenderSprite(appState, renderingSpr, appState->GetPixelPerUnit());
    }

    void RenderSpriteDotByDot(IAppState*appState, SpriteTexture *renderingSpr)
    {
        RenderSprite(appState, renderingSpr, 1);
    }

    void RenderSpriteTwoDots(IAppState*appState, SpriteTexture *renderingSpr)
    {
        RenderSprite(appState, renderingSpr, 2);
    }

    std::function<void(IAppState*)> WrapRenderSpriteDotByDot(SpriteTexture *renderingSpr)
    {
        return {[renderingSpr](IAppState* app){ RenderSpriteDotByDot(app, renderingSpr);}};
    }
}
