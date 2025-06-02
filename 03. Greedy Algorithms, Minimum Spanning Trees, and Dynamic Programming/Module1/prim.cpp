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
// prim O(mn)
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
// prim Fast using Heap : O(mlog(n))
vector<pair<int, pair<int, int>>> primFast(Graph &G, int s)
{
    auto g = G.getAdjList();
    int n = g.size();
    
    // Priority queue for ExtractMin: {weight, {vertex, parent}}
    priority_queue<pair<int, pair<int, int>>, 
                   vector<pair<int, pair<int, int>>>, 
                   greater<pair<int, pair<int, int>>>> pq;
    
    unordered_set<int> X;
    vector<pair<int, pair<int, int>>> T; 
    
    pq.push({0, {s, -1}});  // {weight, {vertex, parent}}
    
    while (!pq.empty() && X.size() < n) {
        auto current = pq.top();
        pq.pop();
        
        int weight = current.first;
        int u = current.second.first;
        int parent = current.second.second;
        
        // Skip if already in MST (handles duplicate entries)
        if (X.find(u) != X.end()) continue;
        
        X.insert(u);
        
        if (parent != -1) {
            T.push_back({weight, {parent, u}});
        }
        
        // Add all crossing edges to priority queue
        for (auto& edge : g[u]) {
            int v = edge.first;
            int edgeWeight = edge.second;
            
            if (X.find(v) == X.end()) {  // v ∉ X
                pq.push({edge.second, {edge.first, u}});
            }
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

    auto mst = primFast(g, 0);

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
