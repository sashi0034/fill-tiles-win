//
// Created by sashi0034 on 2022/07/19.
//

#include "cassert"
#include "UpFlag.h"

namespace myUtil{

    bool UpFlag::IsUp() const
    {
        return isUp;
    }

    void UpFlag::GoDown()
    {
        assert(isUp);
        isUp = false;
    }
}
