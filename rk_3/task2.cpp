#include <iostream>
#include <vector>
#include <unordered_set>

class Graph 
{
public:
    Graph(int n) 
    : N(n), adjacencyMatrix(n, std::vector<bool>(n, false)) 
    {
    }

    void addEdge(int from, int to) 
    {
        adjacencyMatrix[from][to] = true;
        adjacencyMatrix[to][from] = true;
    }

    bool isEdge(int from, int to) const 
    {
        return adjacencyMatrix[from][to];
    }

private:
    int N;
    std::vector<std::vector<bool>> adjacencyMatrix;

};

bool isHamiltonianPath(const Graph& graph, const std::vector<int>& path, int N) 
{
    if (path.size() != N) 
    {
        return false;
    }

    std::unordered_set<int> uniqueVertices;
    for (int i = 0; i < N; ++i) 
    {
        if (path[i] < 0 || path[i] >= N) 
        {
            return false;
        }

        uniqueVertices.insert(path[i]);

        if (i > 0 && !graph.isEdge(path[i-1], path[i])) 
        {
            return false;
        }
    }

    return uniqueVertices.size() == N;
}

int main() 
{
    int N, M, K;
    std::cin >> N >> M >> K;

    Graph graph(N);

    for (int i = 0; i < M; ++i) 
    {
        int from, to;
        std::cin >> from >> to;
        graph.addEdge(from, to);
    }

    std::vector<int> path(K);
    for (int i = 0; i < K; ++i) 
    {
        std::cin >> path[i];
    }

    bool isHamiltonian = isHamiltonianPath(graph, path, N);

    std::cout << (isHamiltonian ? 1 : 0) << std::endl;

    return 0;
}