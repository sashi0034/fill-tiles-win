#include "stdafx.h"
#include "DebugMetaInfoView.h"

#include "GameRoot.h"

namespace myGame {
    DebugMetaInfoView::DebugMetaInfoView(GameRoot* root) :
        ActorBase(root->GetChildren()),
        m_TextPassage(initTextPassage(root))
    {
        m_TextPassage.SetPos(VecDouble2{ 4, 4 });
        m_TextPassage.SetAlignment(ETextHorizontalAlign::Left, ETextVerticalAlign::Top);
        m_TextPassage.SetZIndexForeground(10);
        m_TextPassage.UpdateTextAndView("(meta info)");
    }

    void DebugMetaInfoView::Update(IAppState* app)
    {
        auto&& newText = app->GetTime().GetFps().ToString();
        if (newText == m_TextOld) return;

        m_TextPassage.UpdateTextAndView(newText);
        m_TextOld = newText;
    }

    TextPassage DebugMetaInfoView::initTextPassage(GameRoot* root) const
    {
        return TextPassage(
            root->GetAppState(),
            root->RscFont->PixelMPlus24Px.get(),
            Rgba(64, 255, 64),
            Rgba(32, 32, 32));
    }
}
