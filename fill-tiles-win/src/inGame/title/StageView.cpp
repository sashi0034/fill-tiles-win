//
// Created by sashi0034 on 2022/08/27.
//

#include "StageView.h"
#include "../GameRoot.h"
#include "zParam.h"

namespace inGame::title
{
    IAppState *StageViewArgs::GetApp() const
    {
        return SceneRef->RootRef->GetAppState();
    }

    StageView::StageView(const StageViewArgs &args) :
            _screenshot(createScreenshot(args))
    {
        initIndexSprites(args);
        initCrown(args);
    }

    unique_ptr<ScreenshotView> StageView::createScreenshot(const StageViewArgs &args)
    {
        auto screenShot = std::make_unique<ScreenshotView>(
                args.SceneRef,
                args.CenterPos,
                args.ScreenshotPath,
                args.ParentSpr
        );
        return screenShot;
    }

    void StageView::initIndexSprites(const StageViewArgs &args)
    {
        initIndexSpr(args, _tenthsIndexSpr, args.NumStageIndex/10, -1);
        initIndexSpr(args, _onesIndexSpr, args.NumStageIndex%10, 1);
    }

    constexpr double headerCenterY = -88;

    void StageView::initIndexSpr(const StageViewArgs &args, SpriteTexture &spr, int index, double modifierX) const
    {
        constexpr double space = 16;
        constexpr int cellSize = 32;

        spr.SetGraph(args.SceneRef->RootRef->RscImage->numbers_32x32.get());
        spr.SetSrcRect(Rect<int>{Vec2{cellSize * index, 0}, Vec2{cellSize, cellSize}});
        util::SetTextureByCenter(spr, args.CenterPos + Vec2<double>{modifierX * space, headerCenterY});
        spr.SetPositionParent(args.ParentSpr);
        spr.SetZ(zParam::Screenshot-1);
    }

    void StageView::initCrown(const StageViewArgs &args)
    {
        auto&& image =args.SceneRef->RootRef->RscImage->crown.get();
        _crownSpr.SetGraph(image);
        _crownSpr.SetSrcRect(Rect{Vec2{0, 0}, image->GetSize()});
        constexpr double padY = -4;
        util::SetTextureByCenter(_crownSpr, args.CenterPos + Vec2<double>{0, headerCenterY + padY});
        _crownSpr.SetPositionParent(args.ParentSpr);
        _crownSpr.SetZ(zParam::Screenshot);
    }

} // inGame
