#pragma once

#include "Statistics/StatisticCalculator.h"

class Graph;

class DegreeCalculator : public StatisticCalculator<int>
{
    public:
        DegreeCalculator() : StatisticCalculator(DEGREE) {}
        void CalculateSample(Graph* sample);
};