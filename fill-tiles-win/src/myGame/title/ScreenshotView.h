//
// Created by sashi0034 on 2022/08/25.
//

#ifndef FILL_TILES_SCREENSHOTVIEW_H
#define FILL_TILES_SCREENSHOTVIEW_H

#include "MenuScene.h"
#include <future>

namespace myGame::title
{

    class ScreenshotView : public ActorBase
    {
    public:
        explicit ScreenshotView(MenuScene *sceneRef, const Vec2<double> &centerPos, const std::string &filePath,
                                SpriteTexture &parentSpr);
    private:
        MenuScene* const sceneRef;
        Vec2<double> _pos;
        shared_ptr<Graph> _srcImage{};
        SpriteTexture _texture = SpriteTexture::Create();
    };

} // myGame

#endif //FILL_TILES_SCREENSHOTVIEW_H
