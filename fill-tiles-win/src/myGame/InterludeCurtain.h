#pragma once
#include "ActorBase.h"

namespace myGame {
    class GameRoot;

    class InterludeCurtain : public ActorBase
    {
    public:
        InterludeCurtain(GameRoot* root);
        void renderCurtain(IAppState* app, Graph* image, VecInt2 imageSize);
        void Update(IAppState* app) override;
        void StartOpen();
        void StartClose();
        void WaitProcessClose(CoroTaskYield& yield);
        bool IsStopping() const;
    private:
        SpriteTexture _selfSprite = SpriteTexture::Create();
        double _openingRate = 0;
        bool _isOpeningProcess = false;
        bool isClosingProcess() const;
    };
}

