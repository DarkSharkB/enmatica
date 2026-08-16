#pragma once

#ifndef ENMA_TEST_TIMER_HPP
#define ENMA_TEST_TIMER_HPP

#include <chrono>

using flt32 = float;

template<typename _Type = flt32>
class Timer
{
public:
    Timer() = default;
    ~Timer() = default;

    // Use to start or reset timer
    void RestartTimer() 
    {
        startCount = std::chrono::high_resolution_clock::now();
    }

    _Type ElapsedMicroSeconds()
    {
        return std::chrono::duration<_Type, std::micro>(std::chrono::high_resolution_clock::now() - startCount).count();
    }

    _Type ElapsedNanoSeconds()
    {
        return std::chrono::duration<_Type, std::nano>(std::chrono::high_resolution_clock::now() - startCount).count();
    }

    _Type ElapsedMilliSeconds()
    {
        return std::chrono::duration<_Type, std::milli>(std::chrono::high_resolution_clock::now() - startCount).count();
    }

private:
    std::chrono::high_resolution_clock::time_point startCount;
};
#endif // ENMA_TEST_TIMER_HPP