#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"
#include <iostream>
#include <queue>
#include <functional>
#include <vector>

void BFS(const IGraph& graph, int vertex, std::vector<bool>& visited, const std::function<void(int)>& func) 
{
    std::queue<int> qu;
    qu.push(vertex);
    visited[vertex] = true;
    
    while (!qu.empty()) 
    {
        int currentVertex = qu.front();
        qu.pop();
        
        func(currentVertex);
        
        for (int nextVertex : graph.GetNextVertices(currentVertex)) 
        {
            if (!visited[nextVertex]) 
            {
                visited[nextVertex] = true;
                qu.push(nextVertex);
            }
        }
    }
}

void mainBFS(const IGraph& graph, const std::function<void(int)>& func) 
{
    std::vector<bool> visited(graph.VerticesCount(), false);
    
    for (int i = 0; i < graph.VerticesCount(); ++i) 
    {
        if (!visited[i])
        {
            BFS(graph, i, visited, func);
        }
    }
}

void DFS(const IGraph& graph, int vertex, std::vector<bool>& visited, const std::function<void(int)>& func) 
{
    visited[vertex] = true;
    func(vertex);
    
    for (int nextVertex : graph.GetNextVertices(vertex)) 
    {
        if (!visited[nextVertex]) 
        {
            DFS(graph, nextVertex, visited, func);
        }
    }
}

void mainDFS(const IGraph& graph, const std::function<void(int)>& func) 
{
    std::vector<bool> visited(graph.VerticesCount(), false);
    
    for (int i = 0; i < graph.VerticesCount(); ++i) 
    {
        if (!visited[i]) 
        {
            DFS(graph, i, visited, func);
        }
    }
}

void printGraph(const IGraph& graph) 
{
    std::cout << "Количество вершин: " << graph.VerticesCount() << std::endl;
    std::cout << "BFS: ";
    mainBFS(graph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl << "DFS: ";
    mainDFS(graph, [](int vertex){ std::cout << vertex << " "; });
    std::cout << std::endl << std::endl;
}

int main() 
{
    ListGraph listGraph(7);
    listGraph.AddEdge(0, 1);
    listGraph.AddEdge(0, 5);
    listGraph.AddEdge(1, 2);
    listGraph.AddEdge(1, 3);
    listGraph.AddEdge(1, 5);
    listGraph.AddEdge(1, 6);
    listGraph.AddEdge(3, 2);
    listGraph.AddEdge(3, 4);
    listGraph.AddEdge(3, 6);
    listGraph.AddEdge(5, 4);
    listGraph.AddEdge(5, 6);
    listGraph.AddEdge(6, 4);

    std::cout << "ListGraph:" << std::endl;
    printGraph(listGraph);

    MatrixGraph matrixGraph(listGraph);
    std::cout << "MatrixGraph (скопирован из ListGraph):" << std::endl;
    printGraph(matrixGraph);

    SetGraph setGraph(matrixGraph);
    std::cout << "SetGraph (скопирован из MatrixGraph):" << std::endl;
    printGraph(setGraph);

    ArcGraph arcGraph(setGraph);
    std::cout << "ArcGraph (скопирован из SetGraph):" << std::endl;
    printGraph(arcGraph);

    return 0;
}