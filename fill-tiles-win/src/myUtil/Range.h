//
// Created by sashi0034 on 2022/06/10.
//

#ifndef FILL_TILES_RANGE_H
#define FILL_TILES_RANGE_H

#include <stdafx.h>

namespace myUtil
{
    template <typename T>
    class Range
    {
    private:
        const T m_Min;
        const T m_Max;
    public:
        Range(T minInclusive, T maxInclusive)
        : m_Min(minInclusive), m_Max(maxInclusive)
        {
            assert(minInclusive <= maxInclusive);
        }
        T GetDiff() const{
            return m_Max - m_Min;
        }
        bool IsBetween(T targetValue) const
        {
            return m_Min <= targetValue && targetValue <= m_Max;
        }

        T MakeInRange(T targetValue) const
        {
            return (std::max)(m_Min, (std::min)(targetValue, m_Max));
        }
        T MakeInRangeWithAssert(T targetValue) const
        {
            assert(IsBetween(targetValue));
            return MakeInRange(targetValue);
        }

        T Normalize(T targetValue, const Range<T>&afterRange)
        {
            assert(this->IsBetween(targetValue));
            T normalizedRate = (targetValue - this->m_Min) / (this->m_Max - this->m_Min);
            T result = afterRange.m_Min + (afterRange.m_Max - afterRange.m_Min) * normalizedRate;
            return result;
        }

    };

    using RangeInt = Range<int>;
    using RangeDouble = Range<double>;
}


#endif //FILL_TILES_RANGE_H
