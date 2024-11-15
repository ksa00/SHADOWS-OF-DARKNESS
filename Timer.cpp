#include "Timer.h"

Timer::Timer() : lastTime(std::chrono::high_resolution_clock::now()) {}

float Timer::GetDeltaTime() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    return deltaTime.count();
}
