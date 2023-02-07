//
// Created by sashi0034 on 2022/08/25.
//

#ifndef FILL_TILES_TITLEBACKGROUND_H
#define FILL_TILES_TITLEBACKGROUND_H

#include "../ActorBase.h"

namespace myGame::title
{
    class MenuScene;

    class TitleBackground : public ActorBase
    {
    public:
        TitleBackground(MenuScene* menuScene);
        void Update(IAppState *appState) override;
    private:
        MenuScene* const menuScene;
        Graph* const _bgChip;
        constexpr static int bgChipSize = 64;
        SpriteTexture _texture = SpriteTexture::Create();
        double _offsetY = 0;

        void render(IAppState* app);
    };

} // myGame

#endif //FILL_TILES_TITLEBACKGROUND_H
