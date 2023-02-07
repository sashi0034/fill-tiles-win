//
// Created by sashi0034 on 2022/08/31.
//

#include "input.h"

namespace myGame::player::input
{

    EAngle GetInputAngle(const Uint8 *keyState)
    {
        if (keyState[SDL_Scancode::SDL_SCANCODE_W]) return EAngle::Up;
        if (keyState[SDL_Scancode::SDL_SCANCODE_A]) return EAngle::Left;
        if (keyState[SDL_Scancode::SDL_SCANCODE_S]) return EAngle::Down;
        if (keyState[SDL_Scancode::SDL_SCANCODE_D]) return EAngle::Right;
        return EAngle::None;
    }

    bool IsPushingConfirm(const Uint8 *keyState)
    {
        return keyState[SDL_Scancode::SDL_SCANCODE_SPACE];
    }

}