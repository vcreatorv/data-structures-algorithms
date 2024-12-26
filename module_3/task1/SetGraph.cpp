#include "SetGraph.h"
#include <cassert>

SetGraph::SetGraph(int size) 
: adjacencySets(size) 
{
}

SetGraph::SetGraph(const IGraph& other) 
: adjacencySets(other.VerticesCount()) 
{
    for (int from = 0; from < other.VerticesCount(); ++from) 
    {
        for (int to : other.GetNextVertices(from)) 
        {
            adjacencySets[from].insert(to);
        }
    }
}

void SetGraph::AddEdge(int from, int to) 
{
    assert(0 <= from && from < adjacencySets.size());
    assert(0 <= to && to < adjacencySets.size());
    adjacencySets[from].insert(to);
}

int SetGraph::VerticesCount() const 
{
    return adjacencySets.size();
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const 
{
    assert(0 <= vertex && vertex < adjacencySets.size());
    return std::vector<int>(adjacencySets[vertex].begin(), adjacencySets[vertex].end());
}

std::vector<int> SetGraph::GetPrevVertices(int vertex) const 
{
    assert(0 <= vertex && vertex < adjacencySets.size());
    std::vector<int> prevVertices;
    for (int i = 0; i < adjacencySets.size(); ++i) 
    {
        // проверка элемента на существование в множестве (либо 0, либо 1)
        if (adjacencySets[i].count(vertex) > 0) 
        {
            prevVertices.push_back(i);
        }
    }
    return prevVertices;
}