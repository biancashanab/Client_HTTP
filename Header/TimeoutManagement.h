#pragma once
#include <chrono>

class TimeoutManagement 
{
public:
    TimeoutManagement() = default;
    TimeoutManagement(double timeoutInSeconds);
    ~TimeoutManagement() = default;

    void start();
    bool isTimeout();

private:
    std::chrono::time_point<std::chrono::steady_clock> startTime;
    std::chrono::duration<double> timeoutDuration;
};
