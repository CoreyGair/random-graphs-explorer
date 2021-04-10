#include "Generators/BarabasiAlbertGenerator.h"

#include "Graph/Graph.h"

#include <algorithm>
#include <random>
#include <vector>

// Generates a random Barabasi-Albert model undirected graph
// generator : pointer to mersene random gen
// n_initial : number of initial connected nodes
// n_additional : number of new nodes added
// m_new_connections : number of edges each new node has
Graph* BarabasiAlbertGenerator::GenerateGraph()
{
    // Generate initial adjacency list 
    std::vector<std::vector<int>> adj_list;

    for(int i = 0; i < m_n_initial; ++i){
        std::vector<int> curr_adj_list;
        for(int j = 0; j < m_n_initial; ++j){
            if (i != j) curr_adj_list.push_back(j);
        }
        adj_list.push_back(curr_adj_list);
    }

    // uniform rand dist
    std::uniform_real_distribution<> distribution(0,1);

    int n_edges = m_n_initial * m_n_initial;

    // Add the additional nodes
    for(int i = m_n_initial; i < m_n_initial + m_n_additional; ++i)
    {
        std::vector<int> curr_adj_list;

        // init a list of potential nodes to connect to
        std::vector<int> js;
        for(int j = 0; j < adj_list.size(); ++j) js.push_back(j);

        // add new edges until reach required amt
        while(curr_adj_list.size() < m_m_new_connections)
        {
            std::uniform_int_distribution<> j_dist (0, js.size()-1);

            // pick node to try to connect to 
            int j = js[j_dist(m_generator)];

            // find probability of connecting to it
            double p_i = (double)(adj_list[j].size()) / (double)n_edges;

            float rand_val = distribution(m_generator);
            if (rand_val < p_i)
            {
                curr_adj_list.push_back(j);

                adj_list[j].push_back(i);
            }
        }

        // sort to maintain adj_list ordering
        std::sort(curr_adj_list.begin(), curr_adj_list.end());

        adj_list.push_back(curr_adj_list);
    }

    return new Graph(GetMaxSize(), &adj_list);
}