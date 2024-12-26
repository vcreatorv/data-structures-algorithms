#ifndef SETGRAPH_H
#define SETGRAPH_H

#include "IGraph.h"
#include <vector>
#include <set>

class SetGraph : public IGraph 
{
public:
    SetGraph(int size);
    SetGraph(const IGraph& other);
    ~SetGraph() override = default;

    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::set<int>> adjacencySets;
};

#endif