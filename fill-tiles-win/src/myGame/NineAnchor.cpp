//
// Created by sashi0034 on 2022/08/19.
//

#include "NineAnchor.h"

namespace myGame
{
    NineAnchor::NineAnchor()
    {
        for (int i = 0; i < (int)anchors.size(); ++i)
        {
            auto&& anchor = anchors.at(i);
            anchor.SetUpdateProcess([&anchor, i, this](IAppState* app){
                updatePosition(i, anchor, app);
            });
        }
    }

    void NineAnchor::updatePosition(int index, SpriteTexture &anchor, const IAppState *app) const
    {
        const int posX = (index % 3);
        const int posY = (index / 3);

        auto step = app->GetScreenSize().CastTo<double>() / 2.0;

        anchor.SetPosition(Vec2{step.X * posX, step.Y * posY});
    }

    SpriteTexture& NineAnchor::GetOf(ENineAnchorX anchorX, ENineAnchorY anchorY)
    {
        return anchors.at(int(anchorX) + int(anchorY) * 3);
    }
} // myGame