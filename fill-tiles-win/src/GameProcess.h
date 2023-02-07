//
// Created by sashi0034 on 2022/05/04.
//

#ifndef FILL_TILES_GAMEPROCESS_H
#define FILL_TILES_GAMEPROCESS_H

#include "stdafx.h"
#include "debug.h"
#include "myGame/pixel.h"

class GameProcess {
private:
    static const int pixelPerUnit = myGame::pixel::PixelPerUnit;
    static const int screenWidth = 1280 / pixelPerUnit; // 640
    static const int screenHeight = 720 / pixelPerUnit; // 360
public:
    static int RunGame();
};


#endif //FILL_TILES_GAMEPROCESS_H
