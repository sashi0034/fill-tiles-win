//
// Created by sashi0034 on 2022/07/04.
//

#ifndef FILL_TILES_TEXTPASSAGE_H
#define FILL_TILES_TEXTPASSAGE_H

#include "stdafx.h"

namespace inGame
{
    enum class ETextHorizontalAlign
    {
        Left,
        Center,
        Right,
    };

    enum class ETextVerticalAlign
    {
        Top,
        Center,
        Bottom,
    };

    class TextPassage
    {
    public:
        explicit TextPassage(IAppState *app, FontResource *font);
        TextPassage(IAppState *app, FontResource *font, Rgba foreground, Rgba outline);
        void SetZIndex(int index);
        void SetLineSpacingHeight(int lineHeight);
        void SetPositionParent(SpriteTexture& parent);
        void SetPos(const Vec2<double> &pos);
        void SetAlignment(ETextHorizontalAlign horizontalAlign, ETextVerticalAlign verticalAlign);
        void UpdateView();
        void UpdateTextAndView(const std::string &text);
    private:
        IAppState* m_App;
        Vec2<double> m_Pos{};
        ETextHorizontalAlign m_HorizontalAlign = ETextHorizontalAlign::Left;
        ETextVerticalAlign m_VerticalAlign = ETextVerticalAlign::Top;

        std::vector<unique_ptr<TextureText>> m_TextList{};
        std::vector<std::string> m_Strings{};

        FontResource* m_Font;
        SpriteTexture* m_PositionParent{};
        int m_ZIndex = 0;
        int m_LineSpacingHeight = 4;

        Rgba m_ForegroundColor = Rgba(255, 255, 255);
        Rgba m_OutlineColor = Rgba(64, 64, 64);

        static std::vector<std::string> splitText(const std::string &text, const std::string &separator) ;

        Vec2<double> getBasePosAppliedVertical();

        void updateText(const std::string &text);
    };
}


#endif //FILL_TILES_TEXTPASSAGE_H
