#pragma once

#include <chrono>
#include <iostream>

class Stopwatch
{
    public:
        Stopwatch() { Reset(); }
        void Reset() { m_start_time = std::chrono::high_resolution_clock::now(); }
        float ElapsedTimeMS()
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-m_start_time).count();
        }
        void PrintElapsedTime() { std::cout << ElapsedTimeMS() << " ms" << std::endl; }

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_start_time;
};