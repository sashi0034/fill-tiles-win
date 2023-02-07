//
// Created by sashi0034 on 2022/07/02.
//

#ifndef FILL_TILES_FONT_H
#define FILL_TILES_FONT_H

#include "../../myUtil/myUtil.h"

namespace myGame::resource
{

    class Font
    {
    private:
        IAppState* m_AppStatePtr = nullptr;
    public:
        explicit Font(IAppState* appState);

        const unique_ptr<FontResource> PixelMPlus24Px =
                std::make_unique<FontResource>(
                        m_AppStatePtr, "assets/fonts/PixelMplus-20130602/PixelMplus12-Regular.ttf", 24, 2);

        const unique_ptr<FontResource> KHDotAkihabara32px =
                std::make_unique<FontResource>(
                        m_AppStatePtr, "assets/fonts/khdotfont-20150527/KH-Dot-Akihabara-16.ttf", 32, 2);

        const unique_ptr<FontResource> KHDotHibiya48px =
                std::make_unique<FontResource>(
                        m_AppStatePtr, "assets/fonts/khdotfont-20150527/KH-Dot-Hibiya-24.ttf", 48, 2);

    };

} // myGame::resource

#endif //FILL_TILES_FONT_H
