//
// Created by sashi0034 on 2022/05/18.
//

#ifndef FILL_TILES_RENDERINGPROCESS_H
#define FILL_TILES_RENDERINGPROCESS_H

#include <stdafx.h>
#include "AppState.h"

namespace myUtil{
    class IAppState;
    class SpriteTexture;
}

namespace myUtil::renderingProcess
{

    void RenderSprite(IAppState* appState, SpriteTexture* renderingSpr, double baseScale);
    void RenderSpriteAlignToUnit(IAppState* appState, SpriteTexture* renderingSpr);
    void RenderSpriteDotByDot(IAppState* appState, SpriteTexture* renderingSpr);

    void RenderSprScaleAsDest(IAppState* appState, SpriteTexture* renderingSpr, double baseScale);
    void RenderSprScaleAsDestAlignToUnit(IAppState* appState, SpriteTexture* renderingSpr);
    void RenderSprScaleAsDestDotByDot(IAppState* appState, SpriteTexture* renderingSpr);

    std::function<void(IAppState*)> WrapRenderSpriteDotByDot(SpriteTexture* renderingSpr);
    std::function<void(IAppState*)> WrapRenderSprScaleAsDestAlignToUnit(SpriteTexture* renderingSpr);
    std::function<void(IAppState*)> WrapRenderSprScaleAsDestDotByDot(SpriteTexture* renderingSpr);
}


#endif //FILL_TILES_RENDERINGPROCESS_H
