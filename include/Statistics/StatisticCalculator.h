#pragma once

#include "Statistics/IStatisticCalculator.h"

#include <algorithm>
#include <vector>
#include <mutex>

class Graph;

template<class T>
class StatisticCalculator : public IStatisticCalculator
{
    protected:
        virtual void CalculateSample(Graph* sample) = 0;

    public:
        StatisticCalculator(int stat_flag) : IStatisticCalculator(stat_flag) {}

        // Used to run on std::threads
        void ThreadRun(typename std::vector<Graph*>::iterator begin, typename std::vector<Graph*>::iterator end)
        {
            CalculateSamples(begin, end);
        }

        std::vector<T>& GetSamples() { return samples; }

    protected:
        std::vector<T> samples;
        // This object will be shared by many threads
        std::mutex samples_mutex;

        void AddToAggregates(T new_sample){ samples_mutex.lock(); samples.push_back(new_sample); samples_mutex.unlock(); }
        void AddToAggregates(const std::vector<T>& new_samples)
        { 
            samples_mutex.lock();
            for(auto it = new_samples.begin(); it != new_samples.end(); ++it)
            {
                samples.push_back(*it);
            }
            samples_mutex.unlock();
        }
};