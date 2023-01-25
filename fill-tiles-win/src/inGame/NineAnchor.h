//
// Created by sashi0034 on 2022/08/19.
//

#ifndef FILL_TILES_NINEANCHOR_H
#define FILL_TILES_NINEANCHOR_H

#include "stdafx.h"


namespace inGame
{
    enum class ENineAnchorX
    {
        Left = 0,
        Center,
        Right,
    };

    enum class ENineAnchorY
    {
        Top = 0,
        Middle,
        Bottom
    };

    class NineAnchor
    {
    public:
        NineAnchor();
        SpriteTexture & GetOf(ENineAnchorX anchorX, ENineAnchorY anchorY);
    private:
        std::array<SpriteTexture, 9> anchors = {
                SpriteTexture::Create(), SpriteTexture::Create(), SpriteTexture::Create(),
                SpriteTexture::Create(), SpriteTexture::Create(), SpriteTexture::Create(),
                SpriteTexture::Create(), SpriteTexture::Create(), SpriteTexture::Create()
        };

        void updatePosition(int index, SpriteTexture &anchor, const IAppState *app) const;
    };

} // inGame

#endif //FILL_TILES_NINEANCHOR_H
