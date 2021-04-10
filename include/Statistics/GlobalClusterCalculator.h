#pragma once

#include "Statistics/StatisticCalculator.h"

class Graph;

class GlobalClusterCalculator : public StatisticCalculator<double>
{
    public:
        GlobalClusterCalculator() : StatisticCalculator(GLOB_CLUSTER) {}
        void CalculateSample(Graph* sample);
};