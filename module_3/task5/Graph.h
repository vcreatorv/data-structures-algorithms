// Graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include "Point.h"

class Graph 
{
public:
    Graph(const std::vector<Point>& points);
    int getSize() const;
    double getWeight(int i, int j) const;
    const std::vector<Point>& getPoints() const;

private:
    std::vector<Point> points;
    std::vector<std::vector<double>> adjacency_matrix;
};

#endif // GRAPH_H