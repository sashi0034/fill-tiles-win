//
// Created by sashi0034 on 2022/08/17.
//

#include "IntCounter.h"

namespace myGame
{
    void IntCounter::IncreaseCount()
    {
        m_Count++;
    }

    void IntCounter::DecreaseCount()
    {
        m_Count--;
    }

    int IntCounter::GetCount() const
    {
        return m_Count;
    }

    IntCounter::IntCounter(int count) : m_Count(count)
    {}

    IntCounter::IntCounter()
    {}
} // myGame