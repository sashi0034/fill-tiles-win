//
// Created by sashi0034 on 2022/07/02.
//

#include "TextureText.h"

namespace myUtil
{
    TextureText::TextureText(FontResource *font)
     : m_Font(font)
    {
        m_Texture.SetRenderingProcess([this](IAppState* appState){
            renderingProcess::RenderSpriteDotByDot(appState, &m_Texture);
        });
    }

    void TextureText::SetForeground(Rgba color)
    {
        m_Foreground = color;
    }

    void TextureText::SetOutline(Rgba color)
    {
        m_Outline = color;
    }

    void TextureText::ChangeText(const std::string &inputText)
    {
        const std::string& text = !inputText.empty() ? inputText : " ";

        if (m_Font->HasOutline())
        {
            m_TextGraph = m_Font->MakeTextGraph(text, m_Foreground, m_Outline);
        }
        else
        {
            m_TextGraph = m_Font->MakeTextGraph(text, m_Foreground, Rgba(0, 0, 0));
        }
        m_Texture.SetGraph(m_TextGraph.get());
        m_Texture.SetSrcRect(Rect(Vec2{0, 0}, m_TextGraph->GetSize()));
    }

    SpriteTexture &TextureText::GetTexture()
    {
        return m_Texture;
    }

    Vec2<int> TextureText::GetSize() const
    {
        return m_TextGraph->GetSize();
    }
} // myUtil
