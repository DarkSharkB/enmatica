#pragma once
#include <chrono>

namespace aSE
{
    template<typename T = float>
    class TimeManager
    {
    public:
        TimeManager() = default;
        ~TimeManager() = default;

        // Use to start or reset timer
        void RestartTimer() 
        {
            startCount = std::chrono::high_resolution_clock::now();
        }

        T ElapsedMicroSeconds()
        {
            return std::chrono::duration<T, std::micro>(std::chrono::high_resolution_clock::now() - startCount).count();
        }

        T ElapsedNanoSeconds()
        {
            return std::chrono::duration<T, std::nano>(std::chrono::high_resolution_clock::now() - startCount).count();
        }

        T ElapsedMilliSeconds()
        {
            return std::chrono::duration<T, std::milli>(std::chrono::high_resolution_clock::now() - startCount).count();
        }
    
    private:
        std::chrono::high_resolution_clock::time_point startCount;
    };
}