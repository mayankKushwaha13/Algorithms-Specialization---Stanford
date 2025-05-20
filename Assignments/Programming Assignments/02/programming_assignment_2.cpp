/*
 * File Name    : programming_assignment_2.cpp
 *
 * Credit       : Course     - Graph Search, Shortest Paths, and Data Structures, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-05-20
 *
 * Description  : Programming Assignment 2
 */

#include <bits/stdc++.h>
using namespace std;
vector<int> dijkstra(vector<vector<pair<int, int>>> &g, int s)
{
    int n = g.size();
    vector<int> A(n, 1000000);
    A[s] = 0;
    vector<bool> inX(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> X;
    X.push({0, s});
    while (!X.empty())
    {
        int v = X.top().second;
        int d = X.top().first;
        X.pop();
        if (inX[v])
            continue;
        inX[v] = true;
        for (pair<int, int> p : g[v])
        {
            int w = p.first;
            int le = p.second;
            if (!inX[w] && A[v] != 1000000 && A[v] + le < A[w])
            {
                A[w] = A[v] + le;
                X.push({A[w], w});
            }
        }
    }
    return A;
}
int main()
{
    ifstream testcase("../../test_cases/02/dijkstra.txt");
    if (!testcase.is_open())
    {
        cout << "File could not be opened";
        return 0;
    }
    int maxVertex = 0;
    string line;
    while (getline(testcase, line))
    {
        istringstream iss(line);
        int vertex;
        iss >> vertex;
        maxVertex = max(maxVertex, vertex);
    }
    testcase.clear();
    testcase.seekg(0);

    vector<vector<pair<int, int>>> graph(maxVertex + 1);

    while (getline(testcase, line))
    {
        istringstream iss(line);
        int source;
        iss >> source;
        string pair;
        while (iss >> pair)
        {
            int commaPos = pair.find(',');
            int dest = stoi(pair.substr(0, commaPos));
            int weight = stoi(pair.substr(commaPos + 1));
            graph[source].push_back({dest, weight});
        }
    }
    
    vector<int> distance = dijkstra(graph, 1);
    vector<int> ans = {7,37,59,82,99,115,133,165,188,197};
    for (int i = 0; i < ans.size(); i++){
        cout << distance[ans[i]];
        if (i < ans.size() - 1) cout << ",";
    }
    cout << endl;
}