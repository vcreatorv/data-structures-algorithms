#include <iostream>
#include <vector>
#include <queue>


void BFS(const std::vector<std::vector<int>>& graph, int vertex, std::vector<bool>& visited) 
{
    std::queue<int> qu;
    qu.push(vertex);
    visited[vertex] = true;
    
    while (!qu.empty()) 
    {
        int currentVertex = qu.front();
        qu.pop();
        
        for (int nextVertex : graph[currentVertex]) 
        {
            if (!visited[nextVertex]) 
            {
                visited[nextVertex] = true;
                qu.push(nextVertex);
            }
        }
    }
}

int mainBFS(int n, const std::vector<std::vector<int>>& graph) 
{
    std::vector<bool> visited(n, false);
    int components = 0;
    for (int i = 0; i < n; ++i) 
    {
        if (!visited[i])
        {
            components++;
            BFS(graph, i, visited);
        }
    }

    return components;
}


int main() 
{
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> graph(n);

    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    std::cout << mainBFS(n, graph) << std::endl;

    return 0;
}
