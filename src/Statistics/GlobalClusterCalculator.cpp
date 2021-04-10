#include "Statistics/GlobalClusterCalculator.h"

#include "Graph/Graph.h"

#include <algorithm>
#include <vector>


// Caclulate the global clustering coeff
// number of closed triplets / num total triplets
// where a triplet is 3 verts connected by 2 (open) or 3 (closed) edges
void GlobalClusterCalculator::CalculateSample(Graph* sample)
{
    std::vector<std::vector<int>>* adj_list = sample->GetAdjList();

    int graph_size = sample->GetSize();

    int n_triplets_closed = 0;
    int n_triplets = 0;

    // iterate over all triplets (i,j,k)
    for(auto i = adj_list->cbegin(); i != adj_list->cend(); ++i)
    {
        for(auto j = (*i).cbegin(); j != (*i).cend(); ++j)
        {
            for(auto k = (*i).cbegin(); k != (*i).cend(); ++k)
            {
                if (j == k) continue;

                // bin search as the constructed adj lists are always sorted
                // if this is failing, check that the generator used is outputting sorted adj lists
                bool is_closed = std::binary_search((*adj_list)[*j].begin(), (*adj_list)[*j].end(), *k);
                if (is_closed)
                {
                    ++n_triplets_closed;
                }
                ++n_triplets;
            } 
        }
    }

    double glob_cluster_coeff = (double)n_triplets_closed / (double)n_triplets;

    AddToAggregates(glob_cluster_coeff);
}