/*
 * File Name    : johnson.cpp
 *
 * Credit       : Course     - Shortest Paths Revisited, NP-Complete Problems and What To Do About Them, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-06-07
 *
 * Description  : Implementation of Johnson's Algorithm for APSP
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
        
        if (inX[v]) continue;
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

vector<int> bellmanFord(vector<vector<pair<int, int>>> &g, int n, int source)
{
    vector<int> dist(n, INT_MAX);
    dist[source] = 0;
    
    bool updated;
    for (int i = 0; i < n - 1; i++)
    {
        updated = false;
        
        for (int u = 0; u < n; u++)
        {
            if (dist[u] == INT_MAX) continue;
            
            for (auto &edge : g[u])
            {
                int v = edge.first;
                int weight = edge.second;
                
                if (dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    updated = true;
                }
            }
        }
        
        if (!updated) break;
    }
    return dist;
}

bool hasNegativeCycle(vector<vector<pair<int,int>>> &g, vector<int> dist)
{
    int n = dist.size();
    for (int u = 0; u < n; u++)
    {
        if (dist[u] == INT_MAX) continue;
        
        for (auto &edge : g[u])
        {
            int v = edge.first;
            int weight = edge.second;
            
            if (dist[u] + weight < dist[v])
            {
                return true;
            }
        }
    }
    return false;
}

vector<vector<int>> johnsonsAPSP(vector<vector<pair<int, int>>> &graph, int n)
{
    vector<vector<pair<int, int>>> augmented(n + 1);
    for (int i = 0; i < n; i++)
    {
        augmented[i] = graph[i];
        augmented[n].push_back({i, 0}); 
    }
    
    vector<int> p = bellmanFord(augmented, n + 1, n);
    if (hasNegativeCycle(augmented, p))
    {
        cout << "Graph contains negative cycle!" << endl;
        return {};
    }
    
    vector<vector<pair<int, int>>> reweighted(n);
    for (int u = 0; u < n; u++)
    {
        for (auto &edge : graph[u])
        {
            int v = edge.first, weight = edge.second;
            int newWeight = weight + p[u] - p[v];
            reweighted[u].push_back({v, newWeight});
        }
    }
    
    vector<vector<int>> distances(n, vector<int>(n));
    for (int u = 0; u < n; u++)
    {
        vector<int> dist = dijkstra(reweighted, u);
        for (int v = 0; v < n; v++)
        {
            if (dist[v] == INT_MAX) {
                distances[u][v] = INT_MAX;
            } else {
                distances[u][v] = dist[v] - p[u] + p[v];
            }
        }
    }
    
    return distances;
}

void testJohnsons() {
    vector<vector<pair<int, int>>> graph(4);
    graph[0].push_back({1, 1});   // 0 -> 1: 1
    graph[0].push_back({2, 4});   // 0 -> 2: 4
    graph[1].push_back({2, -3});  // 1 -> 2: -3
    graph[1].push_back({3, 2});   // 1 -> 3: 2
    graph[2].push_back({3, 3});   // 2 -> 3: 3
    
    cout << "=== Testing Johnson's Algorithm ===\n";
    vector<vector<int>> result = johnsonsAPSP(graph, 4);
    
    if (result.empty()) {
        cout << "Algorithm failed (negative cycle detected)\n";
        return;
    }
    
    cout << "All-Pairs Shortest Distances:\n";
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (result[i][j] == INT_MAX) {
                cout << "INF ";
            } else {
                cout << setw(3) << result[i][j] << " ";
            }
        }
        cout << "\n";
    }
}

int main()
{
    testJohnsons();
    return 0;
}
