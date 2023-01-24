//
// Created by sashi0034 on 2022/08/31.
//

#ifndef FILL_TILES_INPUT_H
#define FILL_TILES_INPUT_H

#include <SDL.h>
#include "../Angle.h"

namespace inGame::player::input
{

    EAngle GetInputAngle(const Uint8 *keyState);
    bool IsPushingConfirm(const Uint8 *keyState);

} // inGame

#endif //FILL_TILES_INPUT_H
