//
// Created by sashi0034 on 2022/04/29.
//
#include "log.h"
#include "Time.h"

namespace myUtil
{
    Time Time::globalInstance = Time{};

    Time::Time()
    {
        Restart();
    }

    void Time::Restart()
    {
        m_DeltaMilli = 0;
        m_DeltaSec = 0;
        m_OldTime = std::chrono::system_clock::now();
    }

    void Time::Update(bool isPrintDebugFps)
    {
        auto cur = std::chrono::system_clock::now();
        auto dur = cur - m_OldTime;
        auto milli = std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
        m_DeltaMilli = milli;
        m_DeltaSec = milli / 1000.0;
        m_OldTime = cur;

        countFps(isPrintDebugFps);

    }

    int Time::GetDeltaMilli() const
    {
        return m_DeltaMilli;
    }

    double Time::GetDeltaSec() const
    {
        return m_DeltaSec;
    }

    void Time::countFps(bool isPrintDebugFps)
    {
        m_FpsBuffer += GetDeltaMilli();
        m_FpsCount++;
        if (m_FpsBuffer > 1000)
        {
            m_FpsBuffer -= 1000;
            int ret = m_FpsCount;
            m_FpsCount = 0;
            m_Fps= Fps{ret};
            if (isPrintDebugFps) LOG_INFO << "FPS: " << m_Fps.Value;
        }
    }

    Fps Time::GetFps() const
    {
        return m_Fps;
    }

    std::string Fps::ToString() const
    {
        std::stringstream ss;
        ss << "FPS: " << Value;
        return ss.str();
    }

}


