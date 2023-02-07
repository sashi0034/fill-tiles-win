//
// Created by sashi0034 on 2022/08/27.
//

#ifndef FILL_TILES_TEMPRENDERTARGETCHANGER_H
#define FILL_TILES_TEMPRENDERTARGETCHANGER_H

#include <stdafx.h>

namespace myUtil
{

    class TempRenderTargetChanger
    {
    public:
        [[nodiscard("Keep it in scope.")]] explicit TempRenderTargetChanger(SDL_Renderer* renderer);
        TempRenderTargetChanger* ChangeInScope(SDL_Texture* changingTarget);
        void RenderClearTransparent();
        ~TempRenderTargetChanger();
    private:
        SDL_Renderer* const renderer;
        SDL_Texture* const beforeTexture;
    };

} // myUtil

#endif //FILL_TILES_TEMPRENDERTARGETCHANGER_H
