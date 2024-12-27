#include <iostream>
#include <vector>
#include <set>
#include <limits>

class SetGraph 
{
public:
    SetGraph(int vertices, int a, int b) 
    : n(vertices), adjacency_set(vertices) 
    {
        for (int i = 0; i < n; ++i) {
            addEdge(i, (i + 1) % n, a);
            addEdge(i, (static_cast<long long>(i) * i + 1) % n, b);
        }
    }

private:
    void addEdge(int u, int v, int w) 
    {
        adjacency_set[u].emplace_back(v, w);
    }

public:
    int dijkstra(int s, int t) 
    {
        std::vector<int> shortest_distance(n, std::numeric_limits<int>::max());
        std::set<std::pair<int, int>> priority_queue;

        shortest_distance[s] = 0;
        priority_queue.insert({0, s});

        while (!priority_queue.empty()) 
        {
            int u = priority_queue.begin()->second;
            priority_queue.erase(priority_queue.begin());

            if (u == t) break;

            for (const auto& [v, w] : adjacency_set[u]) 
            {
                if (shortest_distance[u] + w < shortest_distance[v]) 
                {
                    priority_queue.erase({shortest_distance[v], v});
                    shortest_distance[v] = shortest_distance[u] + w;
                    priority_queue.insert({shortest_distance[v], v});
                }
            }
        }

        return shortest_distance[t];
    }

private:
    int n;
    std::vector<std::vector<std::pair<int, int>>> adjacency_set;
};

int main() 
{
    int a, b;
    int M, x, y;
    std::cin >> a >> b >> M >> x >> y;

    SetGraph graph(M, a, b);
    int result = graph.dijkstra(x, y);
    
    std::cout << result << std::endl;

    return 0;
}