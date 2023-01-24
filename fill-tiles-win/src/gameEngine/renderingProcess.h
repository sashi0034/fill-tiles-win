//
// Created by sashi0034 on 2022/05/18.
//

#ifndef FILL_TILES_RENDERINGPROCESS_H
#define FILL_TILES_RENDERINGPROCESS_H

#include "SDL.h"
#include "SDL_image.h"
#include "AppState.h"
#include <functional>

namespace gameEngine{
    class IAppState;
    class SpriteTexture;
}

namespace gameEngine::renderingProcess
{

    void RenderSprite(IAppState* appState, SpriteTexture* renderingSpr, double baseScale);
    void RenderSpriteAlignToUnit(IAppState* appState, SpriteTexture* renderingSpr);
    void RenderSpriteDotByDot(IAppState* appState, SpriteTexture* renderingSpr);
    // void RenderSpriteTwoDots(IAppState* appState, SpriteTexture* renderingSpr);

    std::function<void(IAppState*)> WrapRenderSpriteDotByDot(SpriteTexture* renderingSpr);
}


#endif //FILL_TILES_RENDERINGPROCESS_H
