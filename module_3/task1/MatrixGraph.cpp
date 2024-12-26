#include "MatrixGraph.h"
#include <cassert>

MatrixGraph::MatrixGraph(int size) 
: adjacencyMatrix(size, std::vector<bool>(size, false)) 
{
}

MatrixGraph::MatrixGraph(const IGraph& other) 
: adjacencyMatrix(other.VerticesCount(), std::vector<bool>(other.VerticesCount(), false)) 
{
    for (int from = 0; from < other.VerticesCount(); ++from) 
    {
        for (int to : other.GetNextVertices(from)) 
        {
            adjacencyMatrix[from][to] = true;
        }
    }
}

void MatrixGraph::AddEdge(int from, int to) 
{
    assert(0 <= from && from < adjacencyMatrix.size());
    assert(0 <= to && to < adjacencyMatrix.size());
    adjacencyMatrix[from][to] = true;
}

int MatrixGraph::VerticesCount() const 
{
    return adjacencyMatrix.size();
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const 
{
    assert(0 <= vertex && vertex < adjacencyMatrix.size());
    std::vector<int> nextVertices;
    for (int i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        if (adjacencyMatrix[vertex][i]) 
        {
            nextVertices.push_back(i);
        }
    }
    return nextVertices;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const 
{
    assert(0 <= vertex && vertex < adjacencyMatrix.size());
    std::vector<int> prevVertices;
    for (int i = 0; i < adjacencyMatrix.size(); ++i) 
    {
        if (adjacencyMatrix[i][vertex]) 
        {
            prevVertices.push_back(i);
        }
    }
    return prevVertices;
}