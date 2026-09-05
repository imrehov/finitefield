#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>

class Timer {
public:
    Timer()
        : m_StartTimePoint{std::chrono::steady_clock::now()}
    {
    }

    ~Timer()
    {
        Stop();
    }

    void Stop()
    {
        if (m_Stopped) {
            return;
        }

        m_Stopped = true;

        auto endTimePoint{std::chrono::steady_clock::now()};

        auto duration {std::chrono::duration_cast<std::chrono::microseconds>(endTimePoint - m_StartTimePoint)};

        double ms{static_cast<double>(duration.count()) / 1000.0};

        std::cout<< duration.count() << "us ("<< ms << "ms)\n";
    }

private:
    std::chrono::steady_clock::time_point m_StartTimePoint;
    bool m_Stopped{false};
};

#endif // TIMER_H