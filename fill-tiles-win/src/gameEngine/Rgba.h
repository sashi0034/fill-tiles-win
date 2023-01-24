//
// Created by sashi0034 on 2022/07/02.
//

#ifndef FILL_TILES_RGBA_H
#define FILL_TILES_RGBA_H

#include "SDL.h"
#include "Range.h"
#include <cstddef>

namespace gameEngine
{
    class Rgba
    {
    public:
        Rgba(int r, int g, int b);
        Rgba(int r, int g, int b, int alpha);
        Rgba& MakeInRange();
        [[nodiscard]] SDL_Color GetSdlColor() const;

    private:
        static inline const Range<int> colorRange = Range<int>(0, 255);
        int m_R;
        int m_G;
        int m_B;
        int m_Alpha = 255;
    };

} // gameEngine

#endif //FILL_TILES_RGBA_H
