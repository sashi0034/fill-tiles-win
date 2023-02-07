//
// Created by sashi0034 on 2022/07/06.
//

#include "easing.h"

namespace myUtil::easing
{
    static double powByInt(double value, int times)
    {
        double result = value;

        if (times==0) return 1.0;

        for (int i=0; i<times-1; ++i)
            result *= value;

        return result;
    }

    double EaseOutBack(double percent)
    {
        constexpr double c1 = 1.70158;
        constexpr double c3 = c1 + 1;

        return 1 + c3 * powByInt(percent - 1, 3) + c1 * powByInt(percent - 1, 2);
    }

    double EaseInBack(double percent)
    {
        constexpr double c1 = 1.70158;
        constexpr double c3 = c1 + 1;

        return c3 * percent * percent * percent - c1 * percent * percent;
    }
} // myUtil