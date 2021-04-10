#pragma once

#include "Statistics/StatisticCalculator.h"
#include <vector>

class Graph;

class DegeneracyCalculator : public StatisticCalculator<int>
{
    public:
        DegeneracyCalculator() : StatisticCalculator(DEGENERACY) {}
        void CalculateSample(Graph* sample);

    private:
        int ComputeDegreeWithExcluded(std::vector<std::vector<int>>* adj_list, int target, std::vector<int>& excluded);
};