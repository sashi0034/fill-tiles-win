//
// Created by sashi0034 on 2022/08/25.
//

#ifndef FILL_TILES_PIXEL_H
#define FILL_TILES_PIXEL_H

#include "../debug.h"

namespace myGame::pixel{

    constexpr int DotByDot = 1;

    constexpr int PixelPerUnit =
#ifndef MYGAME_DEBUG_FIELDVIEW
        4;
#else
        3;
#endif
    constexpr int PixelPerMat = 16;

}


#endif //FILL_TILES_PIXEL_H
