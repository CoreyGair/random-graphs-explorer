#include "Statistics/BetweenCentCalculator.h"

#include "Graph/Graph.h"

#include <algorithm>
#include <vector>
#include <queue>
#include <stack>

void BetweenCentCalculator::CalculateSample(Graph* sample)
{
    std::vector<std::vector<int>>* adj_list = sample->GetAdjList();

    int graph_size = sample->GetSize();

    std::vector<double> btwn_cent (graph_size,0);

    for (int s = 0; s < graph_size; ++s)
    {
        std::queue<int> Q;
        std::stack<int> S;

        int dist [graph_size]; std::fill_n(dist, graph_size, -1);
        std::vector<int> pred [graph_size];

        int sigma [graph_size] = {0};

        dist[s] = 0;
        sigma[s] = 1;

        Q.push(s);

        while (!Q.empty())
        {
            int v = Q.front(); Q.pop();
            S.push(v);

            for (auto w = adj_list->at(v).begin(); w != adj_list->at(v).end(); ++w)
            {
                if (dist[*w] < 0)
                {
                    dist[*w] = dist[v] + 1;
                    Q.push(*w);
                }
                if (dist[*w] == dist[v] + 1)
                {
                    sigma[*w] += sigma[v];
                    pred[*w].push_back(v);
                }
            }
        }

        double delta [graph_size] = {0.0};
        
        while(!S.empty())
        {
            int w = S.top(); S.pop();
            for(auto v = pred[w].begin(); v != pred[w].end(); ++v)
            {
                delta[*v] += ((double)sigma[*v] / (double)sigma[w]) * (1.0 + delta[w]);
            }
            if (w != s)
            {
                btwn_cent.at(w) += delta[w];
            }
        }
    }

    for (int i = 0; i < graph_size; ++i)
    {
        btwn_cent.at(i) *= 0.5;
    }

    AddToAggregates(btwn_cent);
}