//
// Created by sashi0034 on 2022/04/29.
//

#include <stdafx.h>

#ifndef FILL_TILES_TIME_H
#define FILL_TILES_TIME_H


namespace myUtil
{
    struct Fps
    {
        int Value;
        std::string ToString() const;
    };

    class Time
    {
    private:
        static Time globalInstance;

        std::chrono::system_clock::time_point m_OldTime{};
        int m_DeltaMilli{};
        double m_DeltaSec{};

        int m_FpsCount{};
        int m_FpsBuffer{};

        Fps m_Fps{};

        void countFps(bool isPrintDebugFps);
    public:
        Time();

        int GetDeltaMilli() const;

        double GetDeltaSec() const;

        void Restart();

        void Update(bool isPrintDebugFps= false);

        Fps GetFps() const;
    };
}

#endif //FILL_TILES_TIME_H
