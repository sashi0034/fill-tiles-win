//
// Created by sashi0034 on 2022/08/31.
//

#include "PlusMinusSign.h"

namespace myGame::title
{
    PlusMinusSign::PlusMinusSign(int value) :
            Value(value)
    {
        assert(value == -1 || value == 1 || value == 0);
    }

    PlusMinusSign PlusMinusSign::FromHorizontal(EAngle angle)
    {
        switch (angle)
        {
            case EAngle::Left:
                return PlusMinusSign(-1);
            case EAngle::Right:
                return PlusMinusSign(+1);
            default:
                return PlusMinusSign(0);
        }
    }

    bool PlusMinusSign::HasValue() const
    {
        return Value!=0;
    }
} // myGame
