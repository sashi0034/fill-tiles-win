//
// Created by sashi0034 on 2022/08/27.
//

#include "TempRenderTargetChanger.h"

namespace gameEngine
{
    TempRenderTargetChanger::TempRenderTargetChanger(SDL_Renderer *renderer) :
        renderer(renderer),
        beforeTexture(SDL_GetRenderTarget(renderer))
    {}

    TempRenderTargetChanger* TempRenderTargetChanger::ChangeInScope(SDL_Texture *changingTarget)
    {
        SDL_SetRenderTarget(renderer, changingTarget);
        return this;
    }

    TempRenderTargetChanger::~TempRenderTargetChanger()
    {
        SDL_SetRenderTarget(renderer, beforeTexture);
    }

    void TempRenderTargetChanger::RenderClear()
    {
        SDL_RenderClear(renderer);
    }
} // gameEngine