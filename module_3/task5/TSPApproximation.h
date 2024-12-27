// TSPApproximation.h
#ifndef TSP_APPROXIMATION_H
#define TSP_APPROXIMATION_H

#include "Graph.h"
#include <vector>

class TSPApproximation 
{
public:
    static std::vector<int> findApproximatePath(const Graph& graph);
    static double calculatePathLength(const Graph& graph, const std::vector<int>& path);
};

#endif // TSP_APPROXIMATION_H