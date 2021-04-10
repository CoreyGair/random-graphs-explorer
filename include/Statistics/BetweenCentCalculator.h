#pragma once

#include "Statistics/StatisticCalculator.h"

class Graph;

class BetweenCentCalculator : public StatisticCalculator<double>
{
    public:
        BetweenCentCalculator() : StatisticCalculator(BTWN_CENT) {}
        void CalculateSample(Graph* sample);
};