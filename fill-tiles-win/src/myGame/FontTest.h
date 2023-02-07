
#ifndef FILL_TILES_FONTTEST_H
#define FILL_TILES_FONTTEST_H

#include "SDL_ttf.h"

namespace myGame
{
    class FontTest
    {
    private:
        //static const char* fontPath;
        SDL_Surface *m_Surface;
        SDL_Texture *m_Texture;
        SDL_Renderer *m_Renderer;
    public:
        FontTest(SDL_Renderer *renderer);

        void Render();
    };
}


#endif //FILL_TILES_FONTTEST_H
