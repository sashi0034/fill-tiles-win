//
// Created by sashi0034 on 2022/06/11.
//

#include "coroUtil.h"

#include "AppState.h"

namespace myUtil::coroUtil{

    CoroTask WaitForTime(CoroTaskYield &yield, const Time &timeSystem, double waitSecond)
    {
        double totalTime = 0;

        while (totalTime<waitSecond)
        {
            double deltaSec = timeSystem.GetDeltaSec();
            totalTime += deltaSec;
            yield();
        }
    }


    CoroTask WaitForTime(CoroTaskYield &yield, double waitSecond)
    {
        WaitForTime(yield, AppState::Global()->GetTime(), waitSecond);
    }

    CoroTask WaitForTrue(CoroTaskYield &yield, const std::function<bool()>& discriminant)
    {
        while (!discriminant())
        {
            yield();
        }
    }
}


