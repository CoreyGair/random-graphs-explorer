#include "Statistics/ComponentCountCalculator.h"

#include "Graph/Graph.h"
#include "Graph/GraphUtil.h"
#include <vector>

void ComponentCountCalculator::CalculateSample(Graph* sample)
{
    int components = 0;
    int size = sample->GetSize();

    std::vector<bool> used (size, false);

    for(int source = 0; source < size; ++source)
    {
        if (used.at(source)) continue;
        std::vector<int> component = GraphUtil::FloodFill(sample, source);
        for(auto it = component.begin(); it != component.end(); ++it)
        {
            used.at(*it) = true;
        }
        ++components;
    }

    AddToAggregates(components);
}