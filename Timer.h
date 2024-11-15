#pragma once
#include <chrono>

class Timer
{
public:
    Timer();

    float GetDeltaTime();

private:
    std::chrono::high_resolution_clock::time_point lastTime;
};
