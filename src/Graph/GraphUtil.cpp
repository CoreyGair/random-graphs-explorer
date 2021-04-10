#include "Graph/GraphUtil.h"

#include "Graph/Graph.h"

#include <queue>
#include <set>
#include <sys/types.h>
#include <vector>

int GraphUtil::LongestShortestPath(Graph* g, int source)
{
    std::vector<std::vector<int>>* adj_list = g->GetAdjList();
    int size = g->GetSize();

    std::queue<int> to_explore;
    std::vector<bool> explored (size, false);
    std::vector<int> dist (size,0);

    to_explore.push(source);
    dist.at(source) = 0;

    int max_dist = 0;

    while(!to_explore.empty())
    {
        int node = to_explore.front(); to_explore.pop();
        explored.at(node) = true;
        
        for(auto it = adj_list->at(node).begin(); it != adj_list->at(node).end(); ++it)
        {
            int neighbour = *it;
            
            if (!explored.at(neighbour))
            {
                to_explore.push(neighbour);
                dist.at(neighbour) = dist.at(node) + 1;

                if (dist.at(neighbour) > max_dist) max_dist = dist.at(neighbour);
            }
        }
    }

    return max_dist;
}

std::vector<int> GraphUtil::FloodFill(Graph* g, int source)
{
    std::vector<std::vector<int>>* adj_list = g->GetAdjList();
    int size = g->GetSize();

    std::queue<int> to_explore;
    std::vector<bool> explored (size, false);

    std::vector<int> output;

    to_explore.push(source);
    output.push_back(source);

    while(!to_explore.empty())
    {
        int node = to_explore.front(); to_explore.pop();
        explored.at(node) = true;
        
        for(auto it = adj_list->at(node).begin(); it != adj_list->at(node).end(); ++it)
        {
            int neighbour = *it;
            
            if (!explored.at(neighbour))
            {
                to_explore.push(neighbour);

                output.push_back(neighbour);
            }
        }
    }

    return output;
}