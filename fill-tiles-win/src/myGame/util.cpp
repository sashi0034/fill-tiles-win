//
// Created by sashi0034 on 2022/07/07.
//

#include "util.h"

namespace myGame
{
    void util::SetTextureByCenter(SpriteTexture &texture, const Vec2<double> &pos, int pixelPerUnit)
    {
        const auto size = texture.GetSrcRect().GetSize().CastTo<double>();
        const double unitRate = double(pixelPerUnit) / pixel::PixelPerUnit;
        texture.SetPosition(pos - size * unitRate / 2.0);
    }

    int util::Mod2(int value, int law)
    {
        int result = value % law;
        while (result < 0)
        {
            result += law;
        }

        return result;
    }

    double util::ModDouble2(double value, double law)
    {
        double result = value;
        while (result > law)
        {
            result -= law;
        }
        while (result < 0)
        {
            result += law;
        }

        return result;
    }

    void util::ClearRendererTransparent(SDL_Renderer* renderer)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
    }

    bool util::IsPushedOk(IAppState* app)
    {
        return app->GetKeyboardState()[SDL_Scancode::SDL_SCANCODE_SPACE];
    }

    Vec2<double> util::GetTextureCentralPos(SpriteTexture &texture)
    {
        const auto pos = texture.GetPosition();

        const auto size = texture.GetSrcRect().GetSize().CastTo<double>();

        return pos + size / 2.0;
    }
}


