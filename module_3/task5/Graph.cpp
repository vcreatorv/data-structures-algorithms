// Graph.cpp
#include "Graph.h"

Graph::Graph(const std::vector<Point>& points)
: points(points) 
{
    int n = points.size();
    adjacency_matrix.resize(n, std::vector<double>(n, 0));
    for (int i = 0; i < n; ++i) 
    {
        for (int j = i + 1; j < n; ++j) 
        {
            double distance = points[i].distanceTo(points[j]);
            adjacency_matrix[i][j] = adjacency_matrix[j][i] = distance;
        }
    }
}

int Graph::getSize() const 
{
    return points.size();
}

double Graph::getWeight(int i, int j) const 
{
    return adjacency_matrix[i][j];
}

const std::vector<Point>& Graph::getPoints() const 
{
    return points;
}