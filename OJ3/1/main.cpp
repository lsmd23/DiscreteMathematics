#include <iostream>
#include <vector>
#include <limits.h> // For INT_MAX

using namespace std;

void printAdjMatrix(const vector<vector<int>> &AdjMatrix)
{
    for (const auto &row : AdjMatrix)
    {
        for (const auto &elem : row)
        {
            cout << elem << " ";
        }
        cout << endl;
    }
}

void printVector(const vector<int> &vec)
{
    for (const auto &elem : vec)
    {
        cout << elem << " ";
    }
    cout << endl;
}

int main()
{
    int n;
    cin >> n;

    vector<vector<int>> AdjMatrix(n + 2, vector<int>(n + 2, 0));
    // Adjacency matrix to store the graph

    vector<int> time_vector(n + 2, 0);
    time_vector[0] = 0;
    time_vector[n + 1] = 0;

    // Initialize the adjacency matrix with -1
    for (int i = 0; i < n + 2; i++)
    {
        for (int j = 0; j < n + 2; j++)
        {
            AdjMatrix[i][j] = -1;
        }
    }

    // Read the edges and fill the adjacency matrix
    for (int i = 0; i < n; i++)
    {
        int vertice_num, time, pre_num;
        cin >> vertice_num >> time >> pre_num;
        time_vector[vertice_num + 1] = time;
        if (pre_num == 0)
        {
            AdjMatrix[0][vertice_num + 1] = time_vector[0];
            // Connect to the source
        }
        else
        {
            for (int j = 0; j < pre_num; j++)
            {
                int pre_vertice_num;
                cin >> pre_vertice_num;
                AdjMatrix[pre_vertice_num + 1][vertice_num + 1] = time_vector[pre_vertice_num + 1];
                // Connect to the predecessor
            }
        }
    }

    for (int i = 0; i < n + 1; i++)
    {
        int j;
        for (j = 0; j < n + 2; j++)
        {
            if (AdjMatrix[i][j] != -1)
                break;
        }
        if (j == n + 2) // If no edges are found, connect to the convergence point
        {
            AdjMatrix[i][n + 1] = time_vector[i];
            // Connect to the convergence point
        }
    }

    // printAdjMatrix(AdjMatrix);

    // Find the longest path
    vector<int> longest_path(n + 2, 0);
    longest_path[0] = 0;
    for (int i = 1; i < n + 2; i++)
    {
        int maximum = -1;
        for (int j = 0; j < n + 2; j++)
        {
            if (AdjMatrix[j][i] != -1) // all predecessors of i
            {
                if (longest_path[j] + AdjMatrix[j][i] > maximum)
                    maximum = longest_path[j] + AdjMatrix[j][i];
            }
        }
        longest_path[i] = maximum;
    }

    // printVector(longest_path);

    // Find the longest path to the convergence point
    vector<int> longest_path_to_convergence(n + 2, 0);
    longest_path_to_convergence[n + 1] = longest_path[n + 1];
    for (int j = n; j >= 0; j--)
    {
        int minimum = INT_MAX;
        for (int i = 0; i < n + 2; i++)
        {
            if (AdjMatrix[j][i] != -1) // all successors of j
            {
                if (longest_path_to_convergence[i] - AdjMatrix[j][i] < minimum)
                    minimum = longest_path_to_convergence[i] - AdjMatrix[j][i];
            }
        }
        longest_path_to_convergence[j] = minimum;
    }

    // printVector(longest_path_to_convergence);

    cout << longest_path[n + 1] << endl;
    for (int i = 1; i < n + 1; i++)
    {
        cout << longest_path_to_convergence[i] - longest_path[i] << endl;
    }
    return 0;
}
