#pragma once
#include "ActorBase.h"

namespace inGame {
    class GameRoot;

    class InterludeCurtain : public ActorBase
    {
    public:
        InterludeCurtain(GameRoot* root);
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

