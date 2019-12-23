#pragma once

#include <chrono>
#include <iostream>

class TimeSystem
{
private:

    static long long deltatime;

public:

    using ClockType = std::chrono::nanoseconds;

    static double DeltaTime()
    {
        return deltatime / (1000 * 1000 * 1000.0);
    }

    static void Update()
    {
        bool call_once = [&]() {deltatime = 0; return true; }();

        static auto current = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        auto c = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        deltatime = c - current;

        current = c;

        static long long sum = 0;
        sum += deltatime;

        //std::cout << DeltaTime() << "sum:" << sum << std::endl;
    }

    static void Init()
    {

    }
};
