//
// Created by sashi0034 on 2022/06/20.
//

#ifndef FILL_TILES_PROCESSTIMER_H
#define FILL_TILES_PROCESSTIMER_H

#include <stdafx.h>

namespace myUtil
{
    enum class EProcessStatus
    {
        Dead,
        Running,
    };

    class ProcessTimer
    {
    public:
        ProcessTimer(std::function<EProcessStatus()> process, double intervalSecond);
        void Update(double deltaSecond);
        [[nodiscard]] EProcessStatus GetStatus() const;
    private:
        EProcessStatus m_Status = EProcessStatus::Dead;
        std::function<EProcessStatus()> m_Process{};
        const double m_Interval{};
        double m_CountTime{};
    };
}


#endif //FILL_TILES_PROCESSTIMER_H
