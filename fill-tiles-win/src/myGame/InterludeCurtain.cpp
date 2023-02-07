#include "stdafx.h"
#include "InterludeCurtain.h"
#include "ZIndex.h"
#include "GameRoot.h"

namespace myGame {
    InterludeCurtain::InterludeCurtain(GameRoot* root) :
        ActorBase(root->GetChildren())
    {
        ZIndexForeground(&_selfSprite).ApplyZ();

        auto&& image = root->RscImage->illust_scenery.get();
        auto&& imageSize = image->GetSize();

        _selfSprite.SetRenderingProcess([this, image, imageSize](IAppState* app) {
            renderCurtain(app, image, imageSize);
        });
    }

    void InterludeCurtain::renderCurtain(IAppState* app, Graph* image, VecInt2 imageSize)
    {
        if (_openingRate == 0) return;

        auto&& screenSize = app->GetRealScreenSize();
        const int srcW = int(_openingRate * imageSize.X);
        const int showingW = _openingRate * screenSize.X;

        // 開けるときと閉じるときで描画ちょっと変える
        if (isClosingProcess())
        {
            auto upSrc = SDL_Rect{ 0, 0, srcW, imageSize.Y / 2 };
            auto upDest = SDL_Rect{ 0, 0, showingW, screenSize.Y / 2 };

            auto downSrc = SDL_Rect{ imageSize.X - srcW, imageSize.Y / 2 , srcW, imageSize.Y / 2 };
            auto downDest = SDL_Rect{ screenSize.X - showingW, screenSize.Y / 2, showingW, screenSize.Y / 2 };

            SDL_RenderCopy(app->GetRenderer(), image->GetSdlTexture(), &upSrc, &upDest);
            SDL_RenderCopy(app->GetRenderer(), image->GetSdlTexture(), &downSrc, &downDest);
        }
        else
        {
            auto upSrc = SDL_Rect{ imageSize.X - srcW, 0, srcW, imageSize.Y / 2 };
            auto upDest = SDL_Rect{ screenSize.X - showingW, 0, showingW, screenSize.Y / 2 };

            auto downSrc = SDL_Rect{ 0, imageSize.Y / 2 , srcW, imageSize.Y / 2 };
            auto downDest = SDL_Rect{ 0, screenSize.Y / 2, showingW, screenSize.Y / 2 };

            SDL_RenderCopy(app->GetRenderer(), image->GetSdlTexture(), &upSrc, &upDest);
            SDL_RenderCopy(app->GetRenderer(), image->GetSdlTexture(), &downSrc, &downDest);
        }
    }

    void InterludeCurtain::Update(IAppState* app)
    {
        constexpr double speed = 2.0;

        _openingRate += app->GetTime().GetDeltaSec() * speed * (_isOpeningProcess ? -1 : 1);

        _openingRate = Range<double>(0, 1).MakeInRange(_openingRate);
    }

    void InterludeCurtain::StartOpen()
    {
        _isOpeningProcess = true;
    }

    void InterludeCurtain::StartClose()
    {
        _isOpeningProcess = false;
    }

    void InterludeCurtain::WaitProcessClose(CoroTaskYield& yield)
    {
        this->StartClose();

        yield();

        coroUtil::WaitForTrue(yield, [this]() {return this->IsStopping(); });

        yield();
    }

    bool InterludeCurtain::IsStopping() const
    {
        return _openingRate == 0 || _openingRate == 1;
    }

    bool InterludeCurtain::isClosingProcess() const
    {
        return !_isOpeningProcess;
    }
}
