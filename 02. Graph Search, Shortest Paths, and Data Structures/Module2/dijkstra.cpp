/*
 * File Name    : dijkstra.cpp
 *
 * Credit       : Course     - Graph Search, Shortest Paths, and Data Structures, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-05-20
 *
 * Description  : Implementation of Dijkstra's Algorithm
 */

#include <bits/stdc++.h>
using namespace std;
vector<int> dijkstra(vector<vector<pair<int, int>>> &g, int s)
{
    int n = g.size();
    vector<int> A(n, INT_MAX);
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
            if (!inX[w] && A[v] != INT_MAX && A[v] + le < A[w])
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
    int n = 8;
    vector<vector<pair<int, int>>> G(n);

    // Add edges: {target_vertex, edge_length}
    G[0].push_back({1, 2});
    G[0].push_back({2, 6});
    G[0].push_back({3, 4});

    G[1].push_back({4, 1});
    G[1].push_back({3, 3});

    G[2].push_back({5, 3});

    G[3].push_back({5, 5});
    G[3].push_back({4, 2});

    G[4].push_back({6, 8});

    G[5].push_back({6, 4});
    G[5].push_back({7, 6});

    int source = 0;
    vector<int> distances = dijkstra(G, source);

    cout << "Shortest path distances from vertex " << source << ":\n";
    for (int i = 0; i < n; i++)
    {
        if (distances[i] == INT_MAX)
        {
            cout << "Vertex " << i << ": ∞\n";
        }
        else
        {
            cout << "Vertex " << i << ": " << distances[i] << "\n";
        }
    }
}
