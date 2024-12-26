#include "ArcGraph.h"
#include <cassert>
#include <algorithm>

ArcGraph::ArcGraph(int size) 
: vertexCount(size) 
{
}

ArcGraph::ArcGraph(const IGraph& other) 
: vertexCount(other.VerticesCount()) 
{
    for (int i = 0; i < other.VerticesCount(); ++i) 
    {
        for (int to : other.GetNextVertices(i)) 
        {
            edges.emplace_back(i, to);
        }
    }
}

void ArcGraph::AddEdge(int from, int to) 
{
    assert(0 <= from && from < vertexCount);
    assert(0 <= to && to < vertexCount);
    edges.emplace_back(from, to);
}

int ArcGraph::VerticesCount() const 
{
    return vertexCount;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const 
{
    assert(0 <= vertex && vertex < vertexCount);
    std::vector<int> nextVertices;
    for (const auto& edge : edges) 
    {
        if (edge.first == vertex) 
        {
            nextVertices.push_back(edge.second);
        }
    }
    return nextVertices;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const 
{
    assert(0 <= vertex && vertex < vertexCount);
    std::vector<int> prevVertices;
    for (const auto& edge : edges) 
    {
        if (edge.second == vertex) 
        {
            prevVertices.push_back(edge.first);
        }
    }
    return prevVertices;
}