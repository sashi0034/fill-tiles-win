//
// Created by sashi0034 on 2022/06/10.
//

#include "cassert"
#include "Angle.h"
#include "math.h"

namespace inGame{
    const std::array<Angle, 4> Angle::EveryAngle = {
            Angle(EAngle::Right),
            Angle(EAngle::Up),
            Angle(EAngle::Left),
            Angle(EAngle::Down)
    };

    Angle::Angle()
    : m_Angle(EAngle::None)
    {}

    Angle::Angle(EAngle angle) : m_Angle(angle)
    {}

    Vec2<int> Angle::ToXY() const
    {
        switch (m_Angle)
        {
            case EAngle::Right:
                return Vec2<int>{1, 0};
            case EAngle::Up:
                return Vec2<int>{0, -1};
            case EAngle::Left:
                return Vec2<int>{-1, 0};
            case EAngle::Down:
                return Vec2<int>{0, 1};
            default:
                break;
        }
        assert(false);
    }

    EAngle Angle::GetKind() const
    {
        return m_Angle;
    }

    Angle Angle::ConvertFrom(Vec2<double> pos)
    {
        // atan2の定義域は -pi ~ pi

        double theta = std::atan2(pos.Y, pos.X);

        if (Range<double>(-M_PI / 4, M_PI / 4).IsBetween(theta))
        {
            return Angle(EAngle::Right);
        }
        else if (Range<double>(-M_PI * 3 / 4, -M_PI / 4).IsBetween(theta))
        {
            return Angle(EAngle::Up);
        }
        else if (Range<double>(M_PI / 4, M_PI * 3 / 4).IsBetween(theta))
        {
            return Angle(EAngle::Down);
        }
        else
        {
            return Angle(EAngle::Left);
        }
    }

    bool Angle::IsValid() const
    {
        return m_Angle!=EAngle::None;
    }

}