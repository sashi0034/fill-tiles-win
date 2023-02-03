//
// Created by sashi0034 on 2022/07/16.
//

#include "SimpleTextLabel.h"

namespace inGame
{
    SimpleTextLabel::SimpleTextLabel(GameRoot *gameRoot, SpriteTexture &sprRootRef, const Vec2<double> &bgSize)
    : m_SprRootRef(sprRootRef)
    {
        initBackground(gameRoot, bgSize);
    }

    void SimpleTextLabel::initBackground(GameRoot *root, const Vec2<double> &size)
    {
        const auto sideRatio = Vec2{0.1, 0.1};
        m_Background = std::make_unique<NinePatchImage>(
                root->GetAppState(),
                root->RscImage->ui_rounnd_rect_white.get(),
                Vec2{0.0, 0.0}, Vec2<double>{size.X, size.Y}, sideRatio);
        m_Background->GetSprite().SetBlend(GraphBlend(200));
        m_Background->GetSprite().SetPositionParent(m_SprRootRef);
    }

    void SimpleTextLabel::initText(GameRoot *root, const std::string &str, const Vec2<double> &bgSize)
    {
        m_TextPassage = std::make_unique<TextPassage>(root->GetAppState(),
                                                      root->RscFont->KHDotAkihabara32px.get(), Rgba(255, 255, 255), Rgba(16, 16, 16));
        m_TextPassage->SetPos(bgSize / 2.0);
        m_TextPassage->SetAlignment(ETextHorizontalAlign::Center, ETextVerticalAlign::Center);
        m_TextPassage->SetZIndex(1);
        m_TextPassage->SetPositionParent(m_Background->GetSprite());
        m_TextPassage->UpdateTextAndView(str);
    }
} // inGame