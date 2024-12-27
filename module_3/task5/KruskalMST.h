// KruskalMST.h
#ifndef KRUSKAL_MST_H
#define KRUSKAL_MST_H

#include "Graph.h"
#include "DSU.h"
#include <vector>

class KruskalMST 
{
public:
    static std::vector<std::pair<int, int>> findMST(const Graph& graph);
};

#endif // KRUSKAL_MST_H