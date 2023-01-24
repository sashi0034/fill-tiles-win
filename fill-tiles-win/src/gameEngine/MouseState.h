//
// Created by sashi0034 on 2022/06/19.
//

#ifndef FILL_TILES_MOUSESTATE_H
#define FILL_TILES_MOUSESTATE_H

#include "Vec2.h"

namespace gameEngine
{
    enum class EMouseButton{
        Left,
        Middle,
        Right,
        X1,
        X2,
    };

    class IMouseState
    {
    public:
        [[nodiscard]] virtual Vec2<double> GetPosition() const = 0;
        [[nodiscard]] virtual bool GetPushed(EMouseButton button) const = 0;
    };

    class MouseState : public IMouseState
    {
    public:
        [[nodiscard]] Vec2<double> GetPosition() const override;
        void SetPosition(Vec2<double> pos);

        [[nodiscard]] bool GetPushed(EMouseButton button) const override;

        void SetPushed(Uint8 sdlButton, bool isPushed);
    private:
        EMouseButton convertSdlButton(Uint8 sdlButton);

        Vec2<double> m_Pos{};
        bool m_IsPushed[8]{};
    };
}


#endif //FILL_TILES_MOUSESTATE_H
