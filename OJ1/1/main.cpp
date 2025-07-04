#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <string>
#include <algorithm>

using namespace std;

void dfs(int curr, vector<int> &temp_path, vector<int> &visited, // 记录访问情况与临时路径
         set<vector<int>> &path,                                 // 记录路径
         vector<int> &index, vector<int> &succ)
{
    if (curr == index.size() - 2) // 到达终点
    {
        temp_path.push_back(curr);
        path.insert(temp_path);
        temp_path.pop_back();
        return;
    } // 输出路径

    // 检查是否有后继节点
    if (index[curr] == index[curr + 1]) // 无后继节点
        return;

    // // 检查节点是否有自环
    // if (temp_path.size() != 0 && temp_path[temp_path.size() - 1] == curr)
    // {
    //     temp_path.push_back(curr);
    //     return;
    // }

    // 检查路径是否有环
    if (visited[curr] == 1)
        return;

    for (int i = index[curr]; i < index[curr + 1]; i++)
    {
        // // 检查节点是否有自环
        // if (succ[i] == curr)
        //     continue;

        temp_path.push_back(curr);
        visited[curr] = 1;
        // 排除自环，遇到自环则跳过
        // if (succ[i] != curr)
        dfs(succ[i], temp_path, visited, path, index, succ);
        temp_path.pop_back();
        visited[curr] = 0;
    }
}

bool cmp(const vector<int> &a, const vector<int> &b)
{
    auto min_size = min(a.size(), b.size());
    for (int i = 0; i < min_size; i++)
    {
        if (a[i] != b[i])
            return a[i] < b[i];
    }
    return a.size() < b.size(); // 如果前面相同，则比较长度
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> index(n + 1);
    for (int i = 0; i < n + 1; i++)
        cin >> index[i];
    vector<int> succ(m);
    for (int i = 0; i < m; i++)
        cin >> succ[i];

    vector<int> visited(n, 0); // 0表示未访问，1表示已访问

    // vector<int> path;
    vector<int> temp_path;
    set<vector<int>> path;
    // 记录路径

    // 对节点编号为i，其后继节点编号为succ[index[i]],succ[index[i+1]-1]之间的节点

    // 递归实现
    dfs(0, temp_path, visited, path, index, succ);

    if (path.size() == 0)
    {
        cout << "0" << endl;
        return 0;
    }

    vector<vector<int>> result(path.begin(), path.end());

    sort(result.begin(), result.end(), cmp); // 排序

    for (int i = 0; i < result.size(); i++)
    {
        // cout << result[i].size() << " ";
        for (int j = 0; j < result[i].size(); j++)
        {
            cout << result[i][j];
            if (j != result[i].size() - 1)
                cout << "->";
        }
        cout << endl;
    }

    // for (auto it = path.begin(); it != path.end(); it++)
    // {
    //     // string s = "";
    //     // for (int i = 0; i < it->size(); i++)
    //     // {
    //     //     s += to_string((*it)[i]);
    //     //     if (i != it->size() - 1)
    //     //         s += "->";
    //     // }
    //     // cout << s << endl;
    // }

    return 0;
}