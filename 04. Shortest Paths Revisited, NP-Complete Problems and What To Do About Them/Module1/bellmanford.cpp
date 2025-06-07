/*
 * File Name    : bellmanford.cpp
 *
 * Credit       : Course     - Shortest Paths Revisited, NP-Complete Problems and What To Do About Them, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-06-07
 *
 * Description  : Bellman Ford Implementation
 */

#include <bits/stdc++.h>
using namespace std;

void bellmanFord(vector<vector<pair<int, int>>> &g, int n, int source)
{
    vector<int> dist(n, INT_MAX);

    dist[source] = 0;

    bool updated;
    for (int i = 0; i < n - 1; i++)
    {
        updated = false;

        // Iterate through all vertices
        for (int u = 0; u < n; u++)
        {
            if (dist[u] == INT_MAX)
                continue; // Skip unreachable vertices

            // Check all outgoing edges from vertex u
            for (auto &edge : g[u])
            {
                int v = edge.first;       // destination vertex
                int weight = edge.second; // edge weight

                if (dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    updated = true;
                }
            }
        }

        // Early termination optimization
        if (!updated)
            break;
    }
    for (int u = 0; u < n; u++)
    {
        if (dist[u] == INT_MAX)
            continue;

        for (auto &edge : g[u])
        {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v])
            {
                cout << "Graph has negative edge cycle" << endl;
                return;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        dist[i] == INT_MAX ? cout << "Vertex " << i << " unreachable from source" << endl
                           : cout << "Distance of " << i << " from source = " << dist[i] << endl;
    }
}
void testBellmanFord()
{
    // Graph from Roughgarden's slides
    vector<vector<pair<int, int>>> graph1(5);
    // Format: graph[from].push_back({to, weight})

    graph1[0].push_back({1, 2}); // s -> v: 2
    graph1[0].push_back({2, 4}); // s -> w: 4
    graph1[0].push_back({3, 4}); // s -> x: 4
    graph1[1].push_back({2, 2}); // v -> w: 2
    graph1[1].push_back({3, 1}); // v -> x: 1
    graph1[3].push_back({4, 4}); // x -> t: 4

    int source1 = 0; // source vertex s
    int n1 = 5;      // number of vertices

    vector<vector<pair<int, int>>> graph2(4);

    graph2[0].push_back({1, 1});  // s -> a: 1
    graph2[0].push_back({2, 4});  // s -> b: 4
    graph2[1].push_back({2, -3}); // a -> b: -3
    graph2[1].push_back({3, 2});  // a -> c: 2
    graph2[2].push_back({3, 3});  // b -> c: 3

    int source2 = 0;
    int n2 = 4;

    vector<vector<pair<int, int>>> graph3(4);

    graph3[0].push_back({1, 1});  // s -> a: 1
    graph3[1].push_back({2, -3}); // a -> b: -3
    graph3[2].push_back({3, -2}); // b -> c: -2
    graph3[3].push_back({1, 1});  // c -> a: 1 (creates negative cycle)

    int source3 = 0;
    int n3 = 4;
    // Cycle: a -> b -> c -> a has weight: -3 + (-2) + 1 = -4 (negative!)

    vector<vector<pair<int, int>>> graph4(5);

    graph4[0].push_back({1, 2}); // s -> a: 2
    graph4[1].push_back({2, 3}); // a -> b: 3
    // vertices 3 and 4 are disconnected

    int source4 = 0;
    int n4 = 5;

    vector<vector<pair<int, int>>> graph5(1);
    // No edges

    int source5 = 0;
    int n5 = 1;

    cout << "=== Testing Bellman-Ford Algorithm ===\n\n";

    // Test 1: Simple graph
    cout << "Test 1: Simple graph (no negative edges)\n";
    cout << "Expected distances from source 0: [0, 2, 4, 3, 7]\n";
    bellmanFord(graph1, n1, source1);
    cout << "\n\n";

    // Test 2: Graph with negative edges
    cout << "Test 2: Graph with negative edges (no negative cycle)\n";
    cout << "Expected distances from source 0: [0, 1, -2, 1]\n";
    bellmanFord(graph2, n2, source2);
    cout << "\n\n";

    // Test 3: Negative cycle detection
    cout << "Test 3: Graph with negative cycle\n";
    cout << "Should detect negative cycle\n";
    bellmanFord(graph3, n3, source3);
    cout << "\n\n";

    // Test 4: Disconnected graph
    cout << "Test 4: Disconnected graph\n";
    cout << "Expected: [0, 2, 5, ∞, ∞]\n";
    bellmanFord(graph4, n4, source4);
    cout << "\n\n";

    // Test 5: Single vertex
    cout << "Test 5: Single vertex\n";
    cout << "Expected: [0]\n";
    bellmanFord(graph5, n5, source5);
    cout << "\n\n";
}

int main()
{
    testBellmanFord();
}