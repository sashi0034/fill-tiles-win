//
// Created by sashi0034 on 2022/08/27.
//

#ifndef FILL_TILES_STAGECLEARINFOVIEW_H
#define FILL_TILES_STAGECLEARINFOVIEW_H

#include "MenuScene.h"
#include "../NinePatchImage.h"
#include "../TextPassage.h"

namespace myGame::title
{
    struct StageClearInfoViewArgs
    {
        MenuScene* const SceneRef;
    };

    class StageClearInfoView
    {
    public:
        explicit StageClearInfoView(const StageClearInfoViewArgs& args);
        void UpdateText(int mapIndex);
    private:
        unique_ptr<NinePatchImage> _background{};
        unique_ptr<TextPassage> _text;
        StageClearInfoViewArgs _initialArgs;
        void initBackground(const StageClearInfoViewArgs& args);
        void initText(const StageClearInfoViewArgs &args);
    };
}


#endif //FILL_TILES_STAGECLEARINFOVIEW_H
