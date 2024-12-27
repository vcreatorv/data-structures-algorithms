// DSU.h
#ifndef DSU_H
#define DSU_H

#include <vector>

class DSU 
{
public:
    DSU(int n);
    int find(int i);
    void unionSets(int x, int y);

private:
    std::vector<int> parent;
    std::vector<int> rank;
};

#endif // DSU_H