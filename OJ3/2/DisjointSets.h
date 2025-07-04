#pragma once

#include <vector>

class DisjointSets
{
    std::vector<int> parent;
    std::vector<int> rank;
    int size;

private:
    void link(int x, int y) // Link two sets
    {
        if (rank[x] > rank[y])
            parent[y] = x;
        else
        {
            parent[x] = y;
            if (rank[x] == rank[y])
                rank[y]++;
        }
    }

public:
    DisjointSets() {}
    DisjointSets(int n) : size(n)
    {
        parent.resize(n);
        for (int i = 0; i < n; ++i)
            parent[i] = i;

        rank.resize(n, 0);
    }

    int find(int x) // Find the root of the set containing x
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }

    void unionSets(int x, int y) // Union the sets containing x and y
    {
        link(find(x), find(y));
    }
};