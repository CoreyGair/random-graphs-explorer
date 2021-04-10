#pragma once

#include "Statistics/StatisticCalculator.h"

class Graph;

class DiameterCalculator : public StatisticCalculator<int>
{
    public:
        DiameterCalculator() : StatisticCalculator(DIAMETER) {}
        void CalculateSample(Graph* sample);
};