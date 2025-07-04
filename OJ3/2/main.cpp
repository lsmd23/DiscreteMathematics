#include <iostream>
#include <vector>
#include <algorithm>
#include "DisjointSets.h"

using namespace std;

struct Edge
{
    int start;
    int end;
    int weight;

    bool operator<(const Edge &other) const
    {
        return weight < other.weight;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++)
    {
        cin >> edges[i].start >> edges[i].end >> edges[i].weight;
    }
    sort(edges.begin(), edges.end());

    DisjointSets ds(n);
    int sum = 0;

    for (int i = 0; i < m; i++)
    {
        if (ds.find(edges[i].start - 1) != ds.find(edges[i].end - 1))
        {
            ds.unionSets(edges[i].start - 1, edges[i].end - 1);
            sum += edges[i].weight;
        }
    }

    bool connected = true;
    for (int i = 1; i < n; i++)
    {
        if (ds.find(i) != ds.find(0))
        {
            connected = false;
            break;
        }
    }
    if (connected)
        cout << sum << endl;
    else
        cout << -1 << endl;

    return 0;
}

// 5 5
// 2 1 3
// 5 3 5
// 4 1 1
// 4 2 4
// 3 5 1