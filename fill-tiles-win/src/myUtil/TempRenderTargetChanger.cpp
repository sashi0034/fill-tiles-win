//
// Created by sashi0034 on 2022/08/27.
//

#include "TempRenderTargetChanger.h"

namespace myUtil
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

    void TempRenderTargetChanger::RenderClearTransparent()
    {
        RenderClearBy(Rgba(255, 255, 255, 0));
    }

    void TempRenderTargetChanger::RenderClearBy(Rgba color)
    {
        SDL_SetRenderDrawColor(renderer, color.GetR(), color.GetG(), color.GetB(), color.GetAlpha());
        SDL_RenderClear(renderer);
    }
} // myUtil
