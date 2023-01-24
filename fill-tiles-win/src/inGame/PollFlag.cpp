//
// Created by sashi0034 on 2022/09/17.
//

#include "PollFlag.h"

namespace inGame
{

    bool PollFlag::TakePoll()
    {
        bool result = _flag;
        if (_flag) _flag = false;
        return result;
    }

    void PollFlag::PutPoll()
    {
        _flag = true;
    }

    bool PollFlag::GetFlagWithoutTake() const
    {
        return _flag;
    }

    PollFlag::PollFlag(bool flag) : _flag(flag)
    {}
}