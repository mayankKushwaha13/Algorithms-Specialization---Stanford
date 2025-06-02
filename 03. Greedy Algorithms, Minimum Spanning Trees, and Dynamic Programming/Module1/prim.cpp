/*
 * File Name    : prim.cpp
 *
 * Credit       : Course     - Graph Search, Shortest Paths, and Data Structures, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-06-02
 *
 * Description  : Implementation of Prim's MST Algorithm in C++
 */

#include <bits/stdc++.h>
using namespace std;
class Graph
{
    int n;
    vector<vector<pair<int, int>>> adjList;

public:
    Graph(int vertices) : n(vertices), adjList(vertices) {}

    void addEdge(int u, int v, int c)
    {
        adjList[u].push_back({v, c});
        adjList[v].push_back({u, c});
    }
    const vector<vector<pair<int, int>>> &getAdjList() const
    {
        return adjList;
    }
};
vector<pair<int, pair<int, int>>> prim(Graph &G, int s)
{
    unordered_set<int> X;
    X.insert(s);
    auto g = G.getAdjList();
    int n = g.size();
    vector<pair<int, pair<int, int>>> T;
    while (X.size() < n)
    {
        int U = -1;
        pair<int, int> v = {-1, INT_MAX};
        for (int u = 0; u < n; u++)
        {
            if (X.find(u) != X.end())
            {
                for (auto p : g[u])
                {
                    if (p.second < v.second && X.find(p.first) == X.end())
                    {
                        v = p;
                        U = u;
                    }
                }
            }
        }
        if (v.first != -1)
        {
            T.push_back({v.second, {U, v.first}});
            X.insert(v.first);
        }
    }
    return T;
}
int main()
{
    int n = 6;
    Graph g(n);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 1);
    g.addEdge(0, 3, 2);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 4, 3);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 5, 2);
    g.addEdge(4, 5, 1);

    auto mst = prim(g, 0);

    cout << "Prim's MST edges:\n";
    int totalWeight = 0;
    for (auto &edge : mst)
    {
        int weight = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;
        cout << u << "-" << v << " : " << weight << endl;
        totalWeight += weight;
    }
    cout << "Total weight: " << totalWeight << endl;
}
