#include "Statistics/DegreeCalculator.h"

#include "Graph/Graph.h"

#include <vector>

void DegreeCalculator::CalculateSample(Graph* sample)
{
    for(auto node = sample->GetAdjList()->begin(); node != sample->GetAdjList()->end(); ++node)
    {
        int degree = (*node).size();
        AddToAggregates(degree);
    }
}