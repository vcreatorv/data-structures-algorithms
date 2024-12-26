#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <algorithm>

class SetGraph 
{
public:
    SetGraph(int vertices) 
    : n(vertices), adjacency_set(vertices) 
    {
    }

    void addEdge(int u, int v, int w) 
    {
        adjacency_set[u].emplace_back(v, w);
        adjacency_set[v].emplace_back(u, w);
    }

    int dijkstra(int s, int t) 
    {
        std::vector<int> shortest_distance(n, std::numeric_limits<int>::max());
        // первый элемент - вес, второй - вершина
        std::set<std::pair<int, int>> priority_queue;

        shortest_distance[s] = 0;
        priority_queue.insert({0, s});

        while (!priority_queue.empty()) 
        {
            // текущая вершина
            int u = priority_queue.begin()->second;
            priority_queue.erase(priority_queue.begin());

            // кратчайший путь, другие точно больше
            if (u == t) break;

            for (const auto& [v, w] : adjacency_set[u]) 
            {
                if (shortest_distance[u] + w < shortest_distance[v]) 
                {
                    // удаляем более длинный путь
                    priority_queue.erase({shortest_distance[v], v});
                    // обновляем кратчайший путь
                    shortest_distance[v] = shortest_distance[u] + w;
                    // добавляем кратчайший путь
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
    int n, m;
    std::cin >> n >> m;

    SetGraph graph(n);

    for (int i = 0; i < m; ++i) 
    {
        int u, v, w;
        std::cin >> u >> v >> w;
        graph.addEdge(u, v, w);
    }

    int s, t;
    std::cin >> s >> t;
    
    std::cout << graph.dijkstra(s, t) << std::endl;

    return 0;
}