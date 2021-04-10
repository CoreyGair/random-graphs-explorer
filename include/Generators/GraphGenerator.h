#pragma once

#include "Graph/Graph.h"

#include <random>
#include <vector>

// NOTE: All graph generators return a vector<vector<int>> representing the graph as an adjacency list

// ALL generator implementations should ensure each of the sub vectors are sorted, as some of the statistic algorithms use binary search on these

class GraphGenerator
{
    public:
        GraphGenerator(int seed, std::string name) : m_seed(seed), m_generator(seed), model_name(name){}
        virtual Graph* GenerateGraph()=0;
        std::vector<Graph*>& GenerateGraphs(int n)
        {
            graphs = std::vector<Graph*>();
            while(n > 0)
            {
                graphs.push_back(GenerateGraph());
                --n;
            }
            return graphs;
        }

        std::string& GetName() { return model_name; }
        virtual int GetMaxSize() = 0;
    
    protected:
        std::vector<Graph*> graphs;
        int m_seed;
        std::mt19937 m_generator;

        std::string model_name;
};