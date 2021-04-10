#pragma once

#include <algorithm>
#include <vector>
#include <mutex>

#include "Statistics/StatisticDefines.h"

class Graph;

class IStatisticCalculator
{
    protected:
        virtual void CalculateSample(Graph* sample) = 0;
        void CalculateSamples(std::vector<Graph*>::iterator begin, std::vector<Graph*>::iterator end)
        {
            int i =0;
            for(std::vector<Graph*>::iterator graph = begin; graph != end; ++graph)
            {
                CalculateSample(*graph);
            }
        }
        int m_stat_flag;
    public:
        IStatisticCalculator(int stat_flag) : m_stat_flag(stat_flag) {}

        // Used to run on std::threads
        virtual void ThreadRun(typename std::vector<Graph*>::iterator begin, typename std::vector<Graph*>::iterator end) = 0;
        int GetType() { return m_stat_flag; }
};