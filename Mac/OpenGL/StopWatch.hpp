#pragma once

#include <chrono>

class StopWatch
{
public:
    using M = std::chrono::milliseconds;

private:
    std::chrono::time_point<std::chrono::system_clock> begin;

    bool _active;

public:
    StopWatch()
    {
        _active = false;
    }

    inline bool isActive() const
    {
        return _active;
    }

    void Start()
    {
        if (_active)
        {
            return;
        }
        begin = std::chrono::system_clock::now();
        _active = true;
    }

    void Restart()
    {
        Stop();
        Start();
    }

    void Stop()
    {
        _active = false;
    }

    //    template <class TimeType>

    template <typename ClockType>
    long long getTime() const
    {
        if (!_active)
        {
            return 0;
        }

        auto diff = std::chrono::system_clock::now() - begin;
        auto a = std::chrono::duration_cast<ClockType>(diff);
        return a.count();
    }

    inline long long getTime() const
    {
        return getTime<std::chrono::milliseconds>();
    }
};