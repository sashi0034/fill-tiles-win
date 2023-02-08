//
// Created by sashi0034 on 2022/07/04.
//

#include "TextPassage.h"
#include "ZIndex.h"

namespace myGame{

    TextPassage::TextPassage(IAppState *app, FontResource *font)
            : m_App(app), m_Font(font)
    {}

    TextPassage::TextPassage(IAppState *app, FontResource *font, Rgba foreground, Rgba outline)
            : m_App(app), m_Font(font), m_ForegroundColor(foreground), m_OutlineColor(outline)

    {}


    std::vector<std::string> TextPassage::splitText(const std::string &text, const std::string &separator)
    {
        const auto separatorLength = separator.length();

        auto list = std::vector<std::string>();

        if (separatorLength == 0)
            list.push_back(text);
        else
        {
            auto offset = std::string::size_type(0);
            while (true)
            {
                const auto pos = text.find(separator, offset);
                if (pos == std::string::npos)
                {
                    list.push_back(text.substr(offset));
                    break;
                }
                list.push_back(text.substr(offset, pos - offset));
                offset = pos + separatorLength;
            }
        }
        return list;
    }

    void TextPassage::SetZIndex(int index)
    {
        m_ZIndex = index;
        m_IsZIndexForeground = false;
    }

    void TextPassage::SetZIndexForeground(int index)
    {
        m_ZIndex = index;
        m_IsZIndexForeground = true;
    }

    void TextPassage::UpdateTextAndView(const std::string &text)
    {
        updateText(text);

        UpdateView();
    }

    int TextPassage::GetMaxWidth() const
    {
        int result = 0;
        for (auto&& text : m_TextList) {
            auto&& size = text->GetSize();
            result = (std::max)(result, size.X);
        }

        return result;
    }

    void TextPassage::updateText(const std::string &text)
    {
        m_Strings = splitText(text, "<br>");
        const int oldListSize = m_TextList.size();

        // 余分なテキストをカット
        for (int surplusRow = oldListSize-1; surplusRow>=int(m_Strings.size()); --surplusRow)
        {
            m_TextList[surplusRow].reset();
            m_TextList.erase(m_TextList.begin() + surplusRow);
        }

        // 足りなかったら増やす
        for (int row = 0; row<int(m_Strings.size()); ++row)
        {
            if (row>=oldListSize) m_TextList.emplace_back(std::make_unique<TextureText>(m_Font));

            auto& line = *m_TextList[row];
            line.SetForeground(m_ForegroundColor);
            line.SetOutline(m_OutlineColor);
            line.ChangeText(m_Strings[row]);
        }
    }

    void TextPassage::SetPositionParent(SpriteTexture &parent)
    {
        m_PositionParent = &parent;
    }

    void TextPassage::SetPos(const Vec2<double> &pos)
    {
        m_Pos = pos;
    }

    void TextPassage::SetAlignment(ETextHorizontalAlign horizontalAlign, ETextVerticalAlign verticalAlign)
    {
        m_HorizontalAlign = horizontalAlign;
        m_VerticalAlign = verticalAlign;
    }

    void TextPassage::SetScale(VecDouble2 scale)
    {
        m_Scale = scale;
    }

    void TextPassage::HideImmediately()
    {
        setVisibleImmediately(false);
    }

    void TextPassage::ShowImmediately()
    {
        setVisibleImmediately(true);
    }

    void TextPassage::setVisibleImmediately(bool isVisible)
    {
        for (auto&& text : m_TextList) {
            text->GetTexture().SetVisible(isVisible);
        }
    }

    void TextPassage::UpdateView()
    {
        if (m_TextList.empty()) return;

        Vec2<double> basePos = getBasePosAppliedVertical();

        for (int row = 0; row < int(m_TextList.size()); ++row)
        {
            auto &line = *m_TextList[row];

            const double pixelPerUnit = m_App->GetPixelPerUnit();
            const double deltaY = row * (line.GetSize().Y / pixelPerUnit + m_LineSpacingHeight);

            double deltaX = 0;
            if (m_HorizontalAlign == ETextHorizontalAlign::Center) deltaX = -line.GetSize().X / pixelPerUnit / 2.0;
            if (m_HorizontalAlign == ETextHorizontalAlign::Right) deltaX = -line.GetSize().X / pixelPerUnit;

            const Vec2<double> deltaPos = Vec2<double>{deltaX, deltaY};;
            line.GetTexture().SetPosition(basePos + deltaPos);
            line.GetTexture().SetScale(m_Scale);

            if (m_IsZIndexForeground == false)
                ZIndexUi(&line.GetTexture()).SetIndex(m_ZIndex).ApplyZ();
            else
                ZIndexForeground(&line.GetTexture()).SetIndex(m_ZIndex).ApplyZ();
            if (m_PositionParent != nullptr) line.GetTexture().SetPositionParent(*m_PositionParent);
        }
    }

    Vec2<double> TextPassage::getBasePosAppliedVertical()
    {
        Vec2<double> basePos = m_Pos;

        if (m_VerticalAlign != ETextVerticalAlign::Top)
        {
            auto& sampleLine = *m_TextList[0];
            const double sampleLineHeight =  sampleLine.GetSize().Y / double(m_App->GetPixelPerUnit());
            const int textsHeight = (m_TextList.size() - 1) * (sampleLineHeight + m_LineSpacingHeight) + sampleLineHeight;
            if (m_VerticalAlign == ETextVerticalAlign::Center) basePos.Y -= textsHeight / 2.0;
            if (m_VerticalAlign == ETextVerticalAlign::Bottom) basePos.Y -= textsHeight;
        }

        return basePos;
    }

    void TextPassage::SetLineSpacingHeight(int lineHeight)
    {
        m_LineSpacingHeight = lineHeight;
    }



}
