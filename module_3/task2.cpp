#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>

class ListGraph 
{
public:
    ListGraph(int vertices) 
    : adjacencyList(vertices) 
    {
    }

    void addEdge(int from, int to) 
    {
        assert(0 <= from && from < adjacencyList.size());
        assert(0 <= to && to < adjacencyList.size());

        adjacencyList[from].push_back(to);
        adjacencyList[to].push_back(from);
    }

    const std::vector<int> getNeighbors(int vertex) const 
    {
        assert(0 <= vertex && vertex < adjacencyList.size());
        return adjacencyList[vertex];
    }

    int verticesCount() const 
    {
        return adjacencyList.size();
    }

private:
    std::vector<std::vector<int>> adjacencyList;
};

int countShortestPaths(const ListGraph& graph, int start, int end) 
{
    std::vector<int> shortest_paths(graph.verticesCount(), 0);
    std::vector<int> distance(graph.verticesCount(), std::numeric_limits<int>::max());
    std::queue<int> q;

    shortest_paths[start] = 1;
    distance[start] = 0;
    q.push(start);

    while (!q.empty()) 
    {
        int current = q.front();
        q.pop();

        for (int neighbor : graph.getNeighbors(current)) 
        {
            if (distance[current] + 1 < distance[neighbor]) 
            {
                distance[neighbor] = distance[current] + 1;
                shortest_paths[neighbor] = shortest_paths[current];
                q.push(neighbor);
            } 
            else if (distance[neighbor] == distance[current] + 1) 
            {
                shortest_paths[neighbor] += shortest_paths[current];
            }
        }
    }

    return shortest_paths[end];
}

int main() 
{
    int v, n;
    std::cin >> v >> n;

    ListGraph graph(v);

    for (int i = 0; i < n; ++i) 
    {
        int from, to;
        std::cin >> from >> to;
        graph.addEdge(from, to);
    }

    int u, w;
    std::cin >> u >> w;

    std::cout << countShortestPaths(graph, u, w) << std::endl;

    return 0;
}