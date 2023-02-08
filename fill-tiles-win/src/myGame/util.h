//
// Created by sashi0034 on 2022/07/07.
//

#ifndef FILL_TILES_UTIL_H
#define FILL_TILES_UTIL_H

#include "../myUtil/myUtil.h"

#include "./pixel.h"

namespace myGame
{
    namespace util
    {
        Vec2<double> GetTextureCentralPos(SpriteTexture& texture);
        void SetTextureByCenter(SpriteTexture& texture, const Vec2<double>& pos, int pixelPerUnit=pixel::PixelPerUnit);

        int Mod2(int value, int law);
        double ModDouble2(double value, double law);

        void ClearRendererTransparent(SDL_Renderer* renderer);

        bool IsPushedOk(IAppState* app);

        std::string StringfyMMSS(int milliSec);
    }
}


#endif //FILL_TILES_UTIL_H
