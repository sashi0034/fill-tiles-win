//
// Created by sashi0034 on 2022/08/25.
//

#include "ScreenshotView.h"
#include "../GameRoot.h"
#include "./zIndex.h"
#include "../util.h"

namespace inGame::title
{
    ScreenshotView::ScreenshotView(MenuScene *sceneRef, const Vec2<double> &centerPos, const std::string &filePath,
                                   SpriteTexture &parentSpr) :
            ActorBase(sceneRef->GetChildren()),
            sceneRef(sceneRef),
            _pos(centerPos)
    {
        _srcImage = shared_ptr<Graph>(Graph::CreateFromFilePath(sceneRef->RootRef->GetAppState()->GetRenderer(), filePath));
        _texture.SetZ(zIndex::Screenshot);
        _texture.SetGraph(_srcImage.get());
        _texture.SetSrcRect(Rect<int>(Vec2{0, 0}, _srcImage->GetSize()));
        _texture.SetRenderingProcess([this](auto&& app){renderingProcess::RenderSpriteDotByDot(app, &_texture);});
        util::SetTextureByCenter(_texture, centerPos, pixel::DotByDot);
        _texture.SetPositionParent(parentSpr);
    }
} // inGame