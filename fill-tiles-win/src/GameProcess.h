//
// Created by sashi0034 on 2022/05/04.
//

#ifndef FILL_TILES_GAMEPROCESS_H
#define FILL_TILES_GAMEPROCESS_H

#include "debug.h"
#include "inGame/pixel.h"

class GameProcess {
private:
    static const int pixelPerUnit = inGame::pixel::PixelPerUnit;
    static const int screenWidth = 416;
    static const int screenHeight = 240;
public:
    static int RunGame();
};


#endif //FILL_TILES_GAMEPROCESS_H
