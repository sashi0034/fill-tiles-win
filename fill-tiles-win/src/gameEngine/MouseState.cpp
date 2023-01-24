//
// Created by sashi0034 on 2022/06/19.
//

#include <SDL_stdinc.h>
#include "MouseState.h"
#include "SDL.h"
#include "cassert"

namespace gameEngine{

    Vec2<double> MouseState::GetPosition() const
    {
        return m_Pos;
    }

    void MouseState::SetPosition(Vec2<double> pos)
    {
        m_Pos = pos;
    }

    bool MouseState::GetPushed(EMouseButton button) const
    {
        return m_IsPushed[int(button)];
    }

    void MouseState::SetPushed(Uint8 sdlButton, bool isPushed)
    {
        EMouseButton kind = convertSdlButton(sdlButton);

        m_IsPushed[int(kind)] = isPushed;
    }

    EMouseButton MouseState::convertSdlButton(Uint8 sdlButton)
    {
        switch (sdlButton)
        {
            case SDL_BUTTON_LEFT:
                return EMouseButton::Left;
            case SDL_BUTTON_MIDDLE:
                return EMouseButton::Middle;
            case SDL_BUTTON_RIGHT:
                return EMouseButton::Right;
            case SDL_BUTTON_X1:
                return EMouseButton::X1;
            case SDL_BUTTON_X2:
                return EMouseButton::X2;
            default:
                assert(false);
        }
    }
}