//
// Created by sashi0034 on 2022/06/20.
//

#include "ProcessTimer.h"
#include <utility>


namespace gameEngine{

    ProcessTimer::ProcessTimer(std::function<EProcessStatus()> process, double intervalSecond)
    : m_Process(std::move(process)), m_Interval(intervalSecond)
    {
        m_Status = EProcessStatus::Running;
    }

    void ProcessTimer::Update(double deltaSecond)
    {
        if (m_Status==EProcessStatus::Dead) return;

        m_CountTime += deltaSecond;
        while (m_CountTime>m_Interval)
        {
            m_CountTime -= m_Interval;
            m_Status = m_Process();
            if (m_Status == EProcessStatus::Dead) break;
        }
    }

    EProcessStatus ProcessTimer::GetStatus() const
    {
        return m_Status;
    }
}