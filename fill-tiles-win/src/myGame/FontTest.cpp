
#include <stdio.h>
#include <iostream>
#include "FontTest.h"


myGame::FontTest::FontTest(SDL_Renderer* renderer) {
    const char* fontPath = "assets/Mplus2-Regular.ttf";

    TTF_Font* font = TTF_OpenFont(fontPath, 20);
    if (!font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }
    m_Surface = TTF_RenderUTF8_Blended(font, "HelloWorld!", SDL_Color{255,255,255,255});
    m_Texture = SDL_CreateTextureFromSurface(renderer, m_Surface);
    m_Renderer = renderer;
}

void myGame::FontTest::Render() {
    // 文字を描写したTextureのサイズを取得する
    int iw, ih;
    SDL_QueryTexture(m_Texture, NULL, NULL, &iw, &ih);

    SDL_Rect txtRect = SDL_Rect{0, 0, iw, ih};
    SDL_Rect pasteRect = SDL_Rect{200, 200, iw, ih};

    // Textureを描写する
    // 描写元の描写する部分,描写先の描写する部分)
    // サイズが違うと勝手にTextureを伸展してくれる
    SDL_RenderCopy(m_Renderer, m_Texture, &txtRect, &pasteRect);
}
