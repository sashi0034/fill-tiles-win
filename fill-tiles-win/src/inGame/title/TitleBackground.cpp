//
// Created by sashi0034 on 2022/08/25.
//

#include "TitleBackground.h"
#include "MenuScene.h"
#include "../GameRoot.h"
#include "./zIndex.h"

namespace inGame::title
{
    TitleBackground::TitleBackground(MenuScene *menuScene) :
        ActorBase(menuScene->GetChildren()),
        menuScene(menuScene),
        _bgChip(menuScene->RootRef->RscImage->title_bg_chip.get())
    {
        _texture.SetRenderingProcess([this](IAppState* app){ render(app);});
        _texture.SetZ(zIndex::BackGround);
    }

    void TitleBackground::render(IAppState *app)
    {
        const auto screenSize = app->GetRealScreenSize();
        const auto chipSize = _bgChip->GetSize();

        for (int x=-(screenSize.X % chipSize.X)/2; x<screenSize.X; x+=chipSize.X)
        {
            for (int y=-_offsetY; y<screenSize.Y; y+=chipSize.Y)
            {
                _bgChip->RenderGraph(
                        app->GetRenderer(),
                        Vec2{x, y},
                        Rect{Vec2{0, 0}, chipSize},
                        Vec2{1.0, 1.0});
            }
        }
    }

    void TitleBackground::Update(IAppState *appState)
    {
        constexpr double speed = 16;
        _offsetY += appState->GetTime().GetDeltaSec() * speed;
        if (_offsetY>bgChipSize) _offsetY -= bgChipSize;
    }
} // inGame