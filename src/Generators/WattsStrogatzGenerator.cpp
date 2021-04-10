#include "Generators/WattsStrogatzGenerator.h"

#include "Graph/Graph.h"

#include <algorithm>
#include <vector>

// Generates a random Watts-Strogatz model undirected graph
// generator : pointer to mersene random gen
// n : number of nodes
// k : number of next nodes with initial connections
Graph* WattsStrogatzGenerator::GenerateGraph()
{
    // Create initial adjacency matrix    
    // If j is less than k away from i (wrapping around the range [0,m_n]), then is initially connected 
    bool adj_mat [m_n][m_n];
    for(int i = 0; i < m_n; ++i){
        for (int j = i; j < m_n; ++j){
            if (j == i)
            {
                adj_mat[i][j] = false;
            }
            else
            {
                // Ugly, but works (as must take into account both directions of offsets)
                int offset = std::min((j < i) ? m_n - i + j : j - i, (i < j) ? m_n - j + i : i - j);
                adj_mat[i][j] = (offset <= m_k) ? true : false;
                adj_mat[j][i] = adj_mat[i][j];
            }
        }
    }

    // rng uniform [0.0,1.0] distribution
    // use distribution(m_generator) to get a value
    std::uniform_real_distribution<> distribution(0.0,1.0);

    // For each initial edge, rewire it with probability m_b
    // That is, for each edge (i,j), with prob b, replace it with (i,k) s.t. k != i && there is no edge (i,k') s.t k=k'
    for(int i = 0; i < m_n; ++i)
    {
        for(int j = (i+1) % m_n; j != (i+m_k+1) % m_n; j=(j+1)%m_n)
        {
            double rand_val = distribution(m_generator);
            if (rand_val < m_b)
            {
                adj_mat[i][j] = false;
                adj_mat[j][i] = false;
                
                // pick new k s.t. i!=k and adj_mat[i][k] = false
                // first find valid ks
                std::vector<int> ks;
                for(int candidate_k = 0; candidate_k < m_n; ++candidate_k)
                {
                    if (i == candidate_k || adj_mat[i][candidate_k]) continue;
                    ks.push_back(candidate_k);
                }
                
                // construct a distribution to use
                std::uniform_int_distribution<int> k_dist(0,ks.size()-1);

                // pick new k
                int k = ks[k_dist(m_generator)];
                adj_mat[i][k] = true;
                adj_mat[k][i] = true;
            }
        }
    }

    // Generate the adjacency list 
    std::vector<std::vector<int>> adj_list;

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