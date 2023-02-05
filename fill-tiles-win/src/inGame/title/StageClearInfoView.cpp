//
// Created by sashi0034 on 2022/08/27.
//

#include "StageClearInfoView.h"
#include "../GameRoot.h"
#include "../pixel.h"

namespace inGame::title
{
    static const inline Vec2<double> bgSize = Vec2<double>{160.0, 48.0};
    constexpr double centerY = -28;

    StageClearInfoView::StageClearInfoView(const StageClearInfoViewArgs &args)
    {
        initBackground(args);
        initText(args);

    }

    void StageClearInfoView::initBackground(const StageClearInfoViewArgs &args)
    {
        const auto sideRatio = Vec2{0.2, 0.2};

        _background = std::make_unique<NinePatchImage>(
                args.SceneRef->RootRef->GetAppState(),
                args.SceneRef->RootRef->RscImage->ui_black_window.get(),
                Vec2{0.0, 0.0}, Vec2<double>{bgSize.X, bgSize.Y}, sideRatio);
        _background->GetSprite().SetPositionParent(args.SceneRef->RootRef->GetAnchor()->GetOf(ENineAnchorX::Center, ENineAnchorY::Bottom));

        util::SetTextureByCenter(_background->GetSprite(), Vec2<double>(0, centerY), pixel::DotByDot);
    }

    void StageClearInfoView::initText(const StageClearInfoViewArgs &args)
    {
        _text = std::make_unique<TextPassage>(
                args.SceneRef->RootRef->GetAppState(),
                args.SceneRef->RootRef->RscFont->KHDotAkihabara32px.get(),
                Rgba(255, 255, 255), Rgba(16, 16, 16));
        constexpr double padX = 16;
        _text->SetPos( Vec2<double>(-bgSize.X/2.0 + padX, centerY));
        _text->SetAlignment(ETextHorizontalAlign::Left, ETextVerticalAlign::Center);
        _text->SetPositionParent(args.SceneRef->RootRef->GetAnchor()->GetOf(ENineAnchorX::Center, ENineAnchorY::Bottom));
        _text->UpdateTextAndView("最小ステップ数:  0<br>最短クリア時間:  01:23");
    }
}
