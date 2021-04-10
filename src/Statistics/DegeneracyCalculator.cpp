#include "Statistics/DegeneracyCalculator.h"

#include "Graph/Graph.h"
#include <algorithm>
#include <vector>
#include <list>

// Calculates the degeneracy of sample, or the smallest k for which the sample is k-degenerate
// implements the simple algorithm described on wiki (Matula & Beck (1983))
void DegeneracyCalculator::CalculateSample(Graph* sample)
{   
    std::vector<std::vector<int>>* adj_list = sample->GetAdjList();
    int size = sample->GetSize();

    std::vector<int> L;

    int d[size];

    for(int i = 0; i < size; ++i)
    {
        d[i] = ComputeDegreeWithExcluded(adj_list, i, L);
    }

    std::list<int> D[size];
    for(int i = 0; i < size; ++i)
    {
        D[d[i]].push_back(i);
    }

    int k = 0;

    // using a as the loop counter is unused
    for(int a = 0; a < size; ++a)
    {
        int i = 0;
        for(; i < size; ++i)
        {
            if (D[i].size() != 0) break;
        }

        k = std::max(k,i);

        int v = D[i].back(); D[i].pop_back();
        L.push_back(v);

        std::vector<int> v_adj = adj_list->at(v);
        for(auto w = v_adj.cbegin(); w != v_adj.cend(); ++w)
        {
            if (std::find(L.cbegin(), L.cend(), *w) != L.end()) continue;
            D[d[*w]].remove(*w);
            --d[*w];
            D[d[*w]].push_back(*w);
        }
    }

    AddToAggregates(k);
}

int DegeneracyCalculator::ComputeDegreeWithExcluded(std::vector<std::vector<int>>* adj_list, int target, std::vector<int>& excluded)
{
    std::vector<int> target_adj = adj_list->at(target);
    int degree = target_adj.size();

    // loop over excluded verts, reduce degree for each one in the targets adj_list
    for(auto it = excluded.cbegin(); it != excluded.cend(); ++it)
    {
        if (std::binary_search(target_adj.cbegin(), target_adj.cend(), *it)) --degree;
    }

    return degree;
}