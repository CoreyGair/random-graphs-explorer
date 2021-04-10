#include "Statistics/DiameterCalculator.h"

#include "Graph/Graph.h"
#include "Graph/GraphUtil.h"

void DiameterCalculator::CalculateSample(Graph* sample)
{
    int diameter = 0;

    for(int source = 0; source < sample->GetSize(); ++source)
    {        
        int longest_shortest_dist = GraphUtil::LongestShortestPath(sample, source);
        if (longest_shortest_dist > diameter) diameter = longest_shortest_dist;
    }

    AddToAggregates(diameter);
}