//
// Created by sashi0034 on 2022/07/02.
//

#ifndef FILL_TILES_FONTRESOURCE_H
#define FILL_TILES_FONTRESOURCE_H

#include "string"
#include "SDL_ttf.h"
#include "memory"
#include "Rgba.h"
#include "Graph.h"
#include "AppState.h"

namespace myUtil
{
    using std::unique_ptr;

    class FontResource
    {
    public:
        FontResource(IAppState *app, const std::string &fontPath, int fontSize, int outLineWidth);
        ~FontResource();
        unique_ptr<Graph> MakeTextGraph(const std::string &text, Rgba foreground) const;
        unique_ptr<Graph> MakeTextGraph(const std::string &text, Rgba foreground, Rgba outline) const;
        bool HasOutline() const;
    private:
        IAppState* m_App;
        const int m_OutlineWidth;
        TTF_Font* m_Font{};
        TTF_Font* m_FontOutLined = nullptr;
    };

} // myUtil

#endif //FILL_TILES_FONTRESOURCE_H
