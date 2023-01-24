//
// Created by sashi0034 on 2022/07/07.
//

#include "util.h"

namespace inGame
{
    void util::SetTextureByCenter(SpriteTexture &texture, const Vec2<double> &pos, int pixelPerUnit)
    {
        const auto size = texture.GetSrcRect().GetSize().CastTo<double>();
        const double unitRate = double(pixelPerUnit) / pixel::PixelPerUnit;
        texture.SetPosition(pos - size * unitRate / 2.0);
    }

    Vec2<double> util::GetTextureCentralPos(SpriteTexture &texture)
    {
        const auto pos = texture.GetPosition();

        const auto size = texture.GetSrcRect().GetSize().CastTo<double>();

        return pos + size / 2.0;
    }
}


