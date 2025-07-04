#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>  // for INT_MAX
#include <utility>   // for pair
#include <algorithm> // for sort

using namespace std;

class Vertex
{
public:
    int num; // vertex number
    // vector<Vertex> adj; // adjacency list
    int distance;
    bool discovered; // flag to check if vertex is discovered

    Vertex() : num(0), distance(INT_MAX), discovered(false) {}            // constructor to initialize vertex
    Vertex(int _num) : num(_num), distance(INT_MAX), discovered(false) {} // constructor to initialize vertex with number
};

template <typename T>
class Greater
{
public:
    bool operator()(T t1, T t2) const
    {
        return t1.distance > t2.distance; // compare two vertices based on distance
    }
};

class Edge
{
public:
    int end;    // end vertex number
    int weight; // edge weight

    Edge() : end(0), weight(0) {}                               // constructor to initialize edge
    Edge(int _end, int _weight) : end(_end), weight(_weight) {} // constructor to initialize edge with end vertex and weight
};

class Graph
{
public:
    // int n, m; // n: number of vertices, m: number of edges
    vector<Vertex> vertices; // vertex list
    // vector<Vertex> vertices_n; // vertex list
    vector<vector<Edge>> adj; // adjacency list
};

int main()
{
    int n, m;
    cin >> n >> m;

    Graph g;
    for (int i = 0; i < n; i++)
    {
        g.vertices.push_back(Vertex(i)); // initialize vertex number
    }
    for (int i = 0; i < n; i++)
    {
        g.vertices.push_back(Vertex(i + n)); // initialize vertex number
    }
    g.adj.resize(2 * n); // resize adjacency list to 2n

    for (int i = 0; i < m; i++)
    {
        int start, end, weight;
        cin >> start >> end >> weight;

        start--; // convert to 0-based index
        end--;   // convert to 0-based index

        g.adj[start].push_back(Edge(end, weight));
        g.adj[end].push_back(Edge(start, weight));
        g.adj[start + n].push_back(Edge(end + n, weight));
        g.adj[end + n].push_back(Edge(start + n, weight));
        g.adj[start].push_back(Edge(end + n, 0));
        g.adj[end].push_back(Edge(start + n, 0));
    }

    // do Dijkstra algorithm
    priority_queue<Vertex, vector<Vertex>, Greater<Vertex>> pq; // priority queue to store vertices based on distance
    g.vertices[0].distance = 0;                                 // set distance of source vertex to 0
    pq.push(g.vertices[0]);                                     // push source vertex to priority queue

    bool connected_flag = false;
    while (!pq.empty())
    {
        Vertex current_v = pq.top();
        pq.pop();
        if (current_v.discovered)
        {
            continue;
        }
        for (int i = 0; i < g.adj[current_v.num].size(); ++i)
        {
            if (!g.vertices[g.adj[current_v.num][i].end].discovered &&
                current_v.distance + g.adj[current_v.num][i].weight < g.vertices[g.adj[current_v.num][i].end].distance)
            {
                g.vertices[g.adj[current_v.num][i].end].distance = current_v.distance + g.adj[current_v.num][i].weight;
                pq.push(g.vertices[g.adj[current_v.num][i].end]);
            }
        }
        current_v.discovered = true;
        if (current_v.num == 2 * n - 1)
        {
            cout << current_v.distance << endl;
            connected_flag = true;
            break;
        }
    }

    if (!connected_flag)
    {
        cout << -1 << endl;
    }

    // cout << g.vertices[2 * n - 1].distance << endl;

    return 0;
}
