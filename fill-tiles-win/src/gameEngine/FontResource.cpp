//
// Created by sashi0034 on 2022/07/02.
//

#include "FontResource.h"

#include <memory>
#include "cassert"

namespace gameEngine
{
    FontResource::FontResource(IAppState *app, const std::string &fontPath, int fontSize, int outLineWidth)
     : m_App(app), m_OutlineWidth(outLineWidth)
    {
        m_Font = TTF_OpenFont(fontPath.c_str(), fontSize);
        assert(m_Font);

        if (outLineWidth != 0)
        {
            m_FontOutLined = TTF_OpenFont(fontPath.c_str(), fontSize);
            assert(m_FontOutLined);
            TTF_SetFontOutline(m_FontOutLined, outLineWidth);
        }
    }

    FontResource::~FontResource()
    {
        if (m_Font!= nullptr) TTF_CloseFont(m_Font);
        if (m_FontOutLined!= nullptr) TTF_CloseFont(m_FontOutLined);
    }

    unique_ptr<Graph> FontResource::MakeTextGraph(const std::string &text, Rgba foreground, Rgba outline) const
    {
        assert(m_FontOutLined);

//        auto surface = TTF_RenderUTF8_Solid(m_Font, text.c_str(), foreground.GetSdlColor());
//        auto surfaceOutlined = TTF_RenderUTF8_Solid(m_FontOutLined, text.c_str(), outline.GetSdlColor());
        auto surface = TTF_RenderUTF8_Blended(m_Font, text.c_str(), foreground.GetSdlColor());
        auto surfaceOutlined = TTF_RenderUTF8_Blended(m_FontOutLined, text.c_str(), outline.GetSdlColor());
        auto foreGroundDestRect = SDL_Rect{m_OutlineWidth, m_OutlineWidth, surface->w, surface->h};

//        SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_NONE);
        SDL_SetSurfaceBlendMode(surface, SDL_BLENDMODE_BLEND);
        SDL_UpperBlit(surface, nullptr, surfaceOutlined, &foreGroundDestRect);

        SDL_FreeSurface(surface);

        return std::make_unique<Graph>(m_App->GetRenderer(), surfaceOutlined);
    }

    unique_ptr<Graph> FontResource::MakeTextGraph(const std::string &text, Rgba foreground) const
    {
        auto surface = TTF_RenderUTF8_Blended(m_Font, text.c_str(), foreground.GetSdlColor());
        return std::make_unique<Graph>(m_App->GetRenderer(), surface);
    }

    bool FontResource::HasOutline() const
    {
        return m_OutlineWidth != 0;
    }

} // gameEngine