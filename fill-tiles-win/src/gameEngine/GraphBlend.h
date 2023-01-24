//
// Created by sashi0034 on 2022/05/14.
//

#ifndef FILL_TILES_GRAPHBLEND_H
#define FILL_TILES_GRAPHBLEND_H

#include <SDL_image.h>

namespace gameEngine
{
    class GraphBlend
    {
        SDL_BlendMode m_Mode = SDL_BLENDMODE_BLEND;
        int m_Pal = 255;
    public:
        GraphBlend();
        explicit GraphBlend(int pal);
        GraphBlend(SDL_BlendMode mode, int pal);

        void GetMode(SDL_BlendMode mode);
        [[nodiscard]] SDL_BlendMode GetMode() const;

        void SetPal(int pal);
        [[nodiscard]] int GetPal() const;
    };
}


#endif //FILL_TILES_GRAPHBLEND_H
