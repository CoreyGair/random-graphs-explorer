#include "Generators/ErdosRenyiGenerator.h"
#include "Graph/Graph.h"

// Generates a random Erdos-Reyni model undirected graph
// generator : pointer to mersene random gen
// n : number of nodes
// p : probability of edge creation
Graph* ErdosRenyiGenerator::GenerateGraph()
{
    // Init adjacency matrix
    bool adj_mat [m_n][m_n];
    for(int i = 0; i < m_n; ++i){
        for (int j = 0; j < m_n; ++j){
            adj_mat[i][j] = false;
        }
    }

    // rng uniform [0.0,1.0] distribution
    std::uniform_real_distribution<> distribution(0.0,1.0);

    // Use rng to generate undirected adjacency matrix
    int ntrue=0;
    for(int i = 0; i < m_n; ++i){
        for (int j = i+1; j < m_n; ++j){
            double randVal = distribution(m_generator);
            if (randVal < m_p)
            {
                adj_mat[i][j] = true;
                adj_mat[j][i] = true;
            }
        }
    }

    std::vector<std::vector<int>> adj_list;

    // Generate the adjacency list 
    for(int i = 0; i < m_n; ++i){
        std::vector<int> curr_adj_list;
        for(int j = 0; j < m_n; ++j){
            if (adj_mat[i][j]) curr_adj_list.push_back(j);
        }
        curr_adj_list.shrink_to_fit();
        adj_list.push_back(curr_adj_list);
    }

    return new Graph(m_n, &adj_list);
}