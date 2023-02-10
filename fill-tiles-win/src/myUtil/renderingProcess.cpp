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
    bool checkRenderableSprite(SpriteTexture* renderingSpr, Graph** sprGraphOut)
    {
        auto renderingGraph = renderingSpr->GetGraph();
        if (renderingGraph == nullptr) return false;
        if (!renderingSpr->GetVisible() || !renderingSpr->GetParentalVisibility()) return false;
        (*sprGraphOut) = renderingGraph;
        return true;
    }

    void RenderSprite(IAppState*appState, SpriteTexture *renderingSpr, double baseScale)
    {
        Graph* renderingGraph{};
        if (checkRenderableSprite(renderingSpr, &renderingGraph) == false) return;

        const int pixelPerUnit = appState->GetPixelPerUnit();

        const auto sprScale = renderingSpr->GetScale();
        auto blend = renderingSpr->GetBlend();
        double rotationDeg = renderingSpr->GetRotationDeg();
        bool isFlip = renderingSpr->GetFlip();
        const auto srcRect = renderingSpr->GetSrcRect();

        auto globalPos = renderingSpr->GetParentalGlobalPosition() + renderingSpr->GetPosition();
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

    void RenderSprScaleAsDest(IAppState* appState, SpriteTexture* renderingSpr, double baseScale)
    {
        Graph* renderingGraph{};
        if (checkRenderableSprite(renderingSpr, &renderingGraph) == false) return;

        const int pixelPerUnit = appState->GetPixelPerUnit();

        const auto sprScale = (renderingSpr->GetScale() * baseScale).CastTo<int>();
        auto blend = renderingSpr->GetBlend();
        double rotationDeg = renderingSpr->GetRotationDeg();
        bool isFlip = renderingSpr->GetFlip();
        const auto srcRect = renderingSpr->GetSrcRect();

        auto globalPos = renderingSpr->GetParentalGlobalPosition() + renderingSpr->GetPosition();
        const Vec2<int> screenPos = (globalPos * pixelPerUnit).CastTo<int>();
        const auto destRect = RectInt{ screenPos, sprScale };

        SDL_Renderer* renderer = appState->GetRenderer();


        renderingGraph->RenderGraphToDest(renderer, srcRect, destRect, rotationDeg, isFlip, blend);
    }

    void RenderSprScaleAsDestAlignToUnit(IAppState* appState, SpriteTexture* renderingSpr)
    {
        RenderSprScaleAsDest(appState, renderingSpr, appState->GetPixelPerUnit());
    }

    void RenderSprScaleAsDestDotByDot(IAppState* appState, SpriteTexture* renderingSpr)
    {
        RenderSprScaleAsDest(appState, renderingSpr, 1);
    }


    std::function<void(IAppState*)> WrapRenderSpriteDotByDot(SpriteTexture *renderingSpr)
    {
        return {[renderingSpr](IAppState* app){ RenderSpriteDotByDot(app, renderingSpr);}};
    }
    std::function<void(IAppState*)> WrapRenderSprScaleAsDestAlignToUnit(SpriteTexture* renderingSpr)
    {
        return { [renderingSpr](IAppState* app) { RenderSprScaleAsDestAlignToUnit(app, renderingSpr); } };
    }
    std::function<void(IAppState*)> WrapRenderSprScaleAsDestDotByDot(SpriteTexture* renderingSpr)
    {
        return { [renderingSpr](IAppState* app) { RenderSprScaleAsDestDotByDot(app, renderingSpr); } };
    }
}
