//
// Created by sashi0034 on 2022/08/17.
//

#ifndef FILL_TILES_INTCOUNTER_H
#define FILL_TILES_INTCOUNTER_H

namespace myUtil
{

    class IntCounter
    {
    public:
        int GetCount() const;
        void IncreaseCount();
        void DecreaseCount();

        IntCounter();
        explicit IntCounter(int count);
    private:
        int m_Count = 0;
    };

} // myUtil

#endif //FILL_TILES_INTCOUNTER_H
