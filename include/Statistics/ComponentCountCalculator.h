#pragma once

#include "Statistics/StatisticCalculator.h"

class Graph;

class ComponentCountCalculator : public StatisticCalculator<int>
{
    public:
        ComponentCountCalculator() : StatisticCalculator(COMPONENTS) {}
        void CalculateSample(Graph* sample);
};