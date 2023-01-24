//
// Created by sashi0034 on 2022/07/02.
//

#ifndef FILL_TILES_TEXTURETEXT_H
#define FILL_TILES_TEXTURETEXT_H

#include "SpriteTexture.h"
#include "FontResource.h"

namespace gameEngine
{
    class TextureText
    {
    public:
        explicit TextureText(FontResource *font);
        void SetForeground(Rgba color);
        void SetOutline(Rgba color);
        void ChangeText(const std::string& inputText);
        SpriteTexture& GetTexture();
        [[nodiscard]] Vec2<int> GetSize() const;
    private:
        FontResource* m_Font;
        SpriteTexture m_Texture = SpriteTexture::Create();
        unique_ptr<Graph> m_TextGraph{};
        Rgba m_Foreground = Rgba(255, 255, 255);
        Rgba m_Outline = Rgba(32, 32, 32);
    };

} // gameEngine

#endif //FILL_TILES_TEXTURETEXT_H
