#pragma once

#include <vector>
class Graph;

class GraphUtil
{
    public:
        // Finds the longest shortest path from a source node
        static int LongestShortestPath(Graph* g, int source);

        // Return a list of nodes connected to the source
        static std::vector<int> FloodFill(Graph* g, int source);
};