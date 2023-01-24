//
// Created by sashi0034 on 2022/06/11.
//

#ifndef FILL_TILES_COROUTIL_H
#define FILL_TILES_COROUTIL_H

#include "CoroTask.h"
#include "WeakPtr.h"
#include "Time.h"

namespace gameEngine::coroUtil
{
    template<typename T>
    CoroTask WaitForExpire(CoroTaskYield &yield, const WeakPtr <T> observer)
    {
        while (!observer.IsNull())
            yield();
    }

    CoroTask WaitForTime(CoroTaskYield& yield, const Time &timeSystem, double waitSecond);
    CoroTask WaitForTime(CoroTaskYield& yield, double waitSecond);

    CoroTask WaitForTrue(CoroTaskYield& yield, const std::function<bool()>& discriminant);
}


#endif //FILL_TILES_COROUTIL_H
