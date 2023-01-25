//
// Created by sashi0034 on 2022/06/10.
//

#ifndef FILL_TILES_ANGLE_H
#define FILL_TILES_ANGLE_H

#include "stdafx.h"

namespace inGame
{
    enum class EAngle
    {
        None = -1,
        Right,
        Up,
        Left,
        Down,
    };

    class Angle
    {
    public:
        Angle();
        Angle(EAngle angle);
        Vec2<int> ToXY() const;
        EAngle GetKind() const;
        bool IsValid() const;
        static Angle ConvertFrom(Vec2<double> pos);

        static const std::array<Angle, 4> EveryAngle;
    private:
        const EAngle m_Angle;
    };
}


#endif //FILL_TILES_ANGLE_H
