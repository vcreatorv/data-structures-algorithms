// TSPApproximation.cpp
#include "TSPApproximation.h"
#include "KruskalMST.h"
#include <stack>

std::vector<int> TSPApproximation::findApproximatePath(const Graph& graph) 
{
    auto mst = KruskalMST::findMST(graph);
    
    std::vector<std::vector<int>> adjacency_list(graph.getSize());
    for (const auto& [u, v] : mst) 
    {
        adjacency_list[u].push_back(v);
        adjacency_list[v].push_back(u);
    }

    std::vector<bool> visited(graph.getSize(), false);
    std::vector<int> path;
    std::stack<int> stack;
    stack.push(0);

    while (!stack.empty()) 
    {
        int v = stack.top();
        stack.pop();

        if (!visited[v]) 
        {
            visited[v] = true;
            path.push_back(v);

            for (int u : adjacency_list[v]) 
            {
                if (!visited[u]) 
                {
                    stack.push(u);
                }
            }
        }
    }

    path.push_back(0); 
    return path;
}

double TSPApproximation::calculatePathLength(const Graph& graph, const std::vector<int>& path) 
{
    double length = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) 
    {
        length += graph.getWeight(path[i], path[i + 1]);
    }
    return length;
}