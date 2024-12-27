// DSU.cpp
#include "DSU.h"

DSU::DSU(int n) : parent(n), rank(n, 0) 
{
    for (int i = 0; i < n; ++i) 
    {
        parent[i] = i;
    }
}

int DSU::find(int i) 
{
    if (parent[i] != i) 
    {
        parent[i] = find(parent[i]);
    }
    return parent[i];
}

void DSU::unionSets(int x, int y) 
{
    int root_x = find(x);
    int root_y = find(y);
    if (root_x != root_y) 
    {
        if (rank[root_x] < rank[root_y]) 
        {
            parent[root_x] = root_y;
        } 
        else if (rank[root_x] > rank[root_y]) 
        {
            parent[root_y] = root_x;
        } 
        else 
        {
            parent[root_y] = root_x;
            rank[root_x]++;
        }
    }
}