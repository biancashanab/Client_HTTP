#include "TimeoutManagement.h"

TimeoutManagement::TimeoutManagement(double timeoutInSeconds)
{
    timeoutDuration = std::chrono::duration<double>(timeoutInSeconds);
}

void TimeoutManagement::start() 
{
    startTime = std::chrono::steady_clock::now();
}

bool TimeoutManagement::isTimeout() 
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = now - startTime;
    return elapsed > timeoutDuration;
}