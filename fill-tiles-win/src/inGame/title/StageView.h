//
// Created by sashi0034 on 2022/08/27.
//

#ifndef FILL_TILES_STAGEVIEW_H
#define FILL_TILES_STAGEVIEW_H

#include "ScreenshotView.h"
#include "../TextPassage.h"

namespace inGame::title
{
    struct StageViewArgs
    {
        const int NumStageIndex;
        MenuScene* const SceneRef;
        SpriteTexture& ParentSpr;
        const Vec2<double> CenterPos;
        const std::string ScreenshotPath;

        IAppState* GetApp() const;
    };

    class StageView
    {
    public:
        explicit StageView(const StageViewArgs& args);
    private:
        const unique_ptr<ScreenshotView> _screenshot;
        SpriteTexture _tenthsIndexSpr = SpriteTexture::Create();
        SpriteTexture _onesIndexSpr = SpriteTexture::Create();
        SpriteTexture _crownSpr = SpriteTexture::Create();

        static unique_ptr<ScreenshotView> createScreenshot(const StageViewArgs &args);
        void initIndexSprites(const StageViewArgs &args);

        void initIndexSpr(const StageViewArgs &args, SpriteTexture &spr, int index, double modifierX) const;
        void initCrown(const StageViewArgs &args);
    };

} // inGame

#endif //FILL_TILES_STAGEVIEW_H
