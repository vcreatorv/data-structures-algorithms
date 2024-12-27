// KruskalMST.cpp
#include "KruskalMST.h"
#include <algorithm>

std::vector<std::pair<int, int>> KruskalMST::findMST(const Graph& graph) 
{
    int n = graph.getSize();
    std::vector<std::tuple<double, int, int>> edges;
    for (int i = 0; i < n; ++i) 
    {
        for (int j = i + 1; j < n; ++j) 
        {
            edges.emplace_back(graph.getWeight(i, j), i, j);
        }
    }
    std::sort(edges.begin(), edges.end());

    DSU dsu(n);

    std::vector<std::pair<int, int>> mst;
    for (const auto& [weight, u, v] : edges) 
    {
        if (dsu.find(u) != dsu.find(v)) 
        {
            mst.emplace_back(u, v);
            dsu.unionSets(u, v);
        }
    }

    return mst;
}