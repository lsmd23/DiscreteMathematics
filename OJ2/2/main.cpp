#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Vertex
{
public:
    int num;                           // vertex number
    int in_degree;                     // in-degree
    Vertex() : num(0), in_degree(0) {} // constructor to initialize vertex
};

class Graph
{
public:
    // int n, m; // n: number of vertices, m: number of edges
    vector<Vertex> vertices; // vertex list
    vector<vector<int>> adj; // adjacency list
};

int main()
{
    int n, m;
    cin >> n >> m;
    Graph g;
    g.vertices.resize(n); // vertex number starts from 1
    for (int i = 0; i < n; i++)
    {
        g.vertices[i].num = i; // initialize vertex number
    }
    g.adj.resize(n); // adjacency list
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        g.adj[u - 1].push_back(v - 1); // add edge u->v
        g.vertices[v - 1].in_degree++; // increment in-degree of vertex v
    }

    stack<Vertex> s; // stack to store vertices with in-degree 0
    for (int i = 0; i < n; i++)
    {
        if (g.vertices[i].in_degree == 0)
        {
            s.push(g.vertices[i]); // push vertex with in-degree 0 to stack
        }
    }
    vector<int> topological_order; // to store the topological order
    while (!s.empty())
    {
        Vertex v = s.top();                     // get the top vertex from stack
        s.pop();                                // pop the vertex from stack
        topological_order.push_back(v.num + 1); // add vertex to topological order
        for (auto u : g.adj[v.num])
        {
            g.vertices[u].in_degree--; // decrement in-degree of adjacent vertex u
            if (g.vertices[u].in_degree == 0)
            {
                s.push(g.vertices[u]); // push vertex with in-degree 0 to stack
            }
        }
    }

    if (topological_order.size() != n)
    {
        cout << "-1" << endl;
    }
    else
    {
        for (int i = 0; i < topological_order.size(); i++)
        {
            cout << topological_order[i] << " "; // print the topological order
        }
    }
    return 0;
}