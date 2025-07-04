#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define INF 1000000000

void printMatrix(vector<vector<int>> matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> matrix(n, vector<int>(n, INF));

    for (int i = 0; i < m; i++)
    {
        int a, b, weight;
        cin >> a >> b >> weight;
        a--;
        b--;
        if (matrix[a][b] == INF)
        {
            matrix[a][b] = weight;
            matrix[b][a] = weight;
            continue;
        }
        else
        {
            matrix[a][b] = min(matrix[a][b], weight);
            matrix[b][a] = min(matrix[b][a], weight);
        }
    }

    for (int i = 0; i < n; i++)
    {
        matrix[i][i] = 0;
    }

    //   printMatrix(matrix);

    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }
    }

    // printMatrix(matrix);

    int diameter = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            diameter = max(diameter, matrix[i][j]);
        }
    }
    if (diameter == INF)
    {
        cout << "-1" << endl;
        return 0;
    }
    cout << diameter << endl;
    return 0;
}