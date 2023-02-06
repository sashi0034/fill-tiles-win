#pragma once
#include "ActorBase.h"

namespace inGame {
    class ScreenSweeper : public ActorBase
    {
    public:
        ScreenSweeper(IChildrenPool<ActorBase>* parent, IAppState* app, ITextureAnimator* animator, SpriteTextureContext* screen);
    private:
        SpriteTexture _spr = SpriteTexture::Create();
        unique_ptr<Graph> _screenshot{};
    };
}
