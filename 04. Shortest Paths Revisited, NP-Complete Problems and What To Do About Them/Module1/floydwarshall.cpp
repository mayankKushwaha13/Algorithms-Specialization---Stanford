/*
 * File Name    : floydwarshall.cpp
 *
 * Credit       : Course     - Shortest Paths Revisited, NP-Complete Problems and What To Do About Them, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-06-07
 *
 * Description  : Floyd-Warshall Algorithm Implementation with Test Cases
 */

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

vector<vector<int>> floydWarshall(vector<vector<int>>& graph, int n) {
    vector<vector<int>> dist(n, vector<int>(n));
    
    // Initialize distance matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) dist[i][j] = 0;
            else if (graph[i][j] != INF) dist[i][j] = graph[i][j];
            else dist[i][j] = INF;
        }
    }
    
    // Main Floyd-Warshall algorithm
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) {
            cout << "Negative Edge Cycle Found"<< endl;
            return {};
        }
    }
    
    return dist;
}
void printMatrix(vector<vector<int>>& dist, int n, string testName) {
    cout << testName << " - Shortest Distance Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF) cout << "INF ";
            else cout << setw(3) << dist[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void testFloydWarshall() {
    cout << "=== Testing Floyd-Warshall Algorithm ===\n\n";
    
    // Test 1: Simple graph with positive weights (from Roughgarden's slides)
    cout << "Test 1: Simple graph with positive weights\n";
    vector<vector<int>> graph1 = {
        {0, 5, INF, 10},
        {INF, 0, 3, INF},
        {INF, INF, 0, 1},
        {INF, INF, INF, 0}
    };
    cout << "Expected: 0->1: 5, 0->2: 8, 0->3: 9, 1->2: 3, 1->3: 4, 2->3: 1\n";
    vector<vector<int>> result1 = floydWarshall(graph1, 4);
    printMatrix(result1, 4, "Test 1");
    
    // Test 2: Graph with negative weights (no negative cycle)
    cout << "Test 2: Graph with negative weights (no negative cycle)\n";
    vector<vector<int>> graph2 = {
        {0, 1, 4},
        {INF, 0, -3},
        {INF, INF, 0}
    };
    cout << "Expected: 0->1: 1, 0->2: -2, 1->2: -3\n";
    vector<vector<int>> result2 = floydWarshall(graph2, 3);
    printMatrix(result2, 3, "Test 2");
    
    // Test 3: Graph with negative cycle
    cout << "Test 3: Graph with negative cycle\n";
    vector<vector<int>> graph3 = {
        {0, 1, INF},
        {INF, 0, -3},
        {-1, INF, 0}
    };
    cout << "Cycle: 0->1->2->0 has weight: 1 + (-3) + (-1) = -3 (negative!)\n";
    vector<vector<int>> result3 = floydWarshall(graph3, 3);
    printMatrix(result3, 3, "Test 3");
    
    // Test 4: Disconnected graph
    cout << "Test 4: Disconnected graph\n";
    vector<vector<int>> graph4 = {
        {0, 2, INF, INF},
        {INF, 0, 3, INF},
        {INF, INF, 0, 1},
        {INF, INF, INF, 0}
    };
    cout << "Vertices 2 and 3 are disconnected from 0 and 1\n";
    vector<vector<int>> result4 = floydWarshall(graph4, 4);
    printMatrix(result4, 4, "Test 4");
    
    // Test 5: Single vertex
    cout << "Test 5: Single vertex\n";
    vector<vector<int>> graph5 = {{0}};
    cout << "Expected: Distance to self = 0\n";
    vector<vector<int>> result5 = floydWarshall(graph5, 1);
    printMatrix(result5, 1, "Test 5");
    
    // Test 6: Complete graph (from search results example)
    cout << "Test 6: Complete graph\n";
    vector<vector<int>> graph6 = {
        {0, 12, 45, 2},
        {1, 0, 45, 32},
        {77, 43, 0, 2},
        {42, 3, 88, 0}
    };
    cout << "Dense graph with multiple paths between vertices\n";
    vector<vector<int>> result6 = floydWarshall(graph6, 4);
    printMatrix(result6, 4, "Test 6");
    
    // Test 7: Triangle with negative edge
    cout << "Test 7: Triangle with negative edge (no cycle)\n";
    vector<vector<int>> graph7 = {
        {0, 4, INF},
        {INF, 0, -5},
        {2, INF, 0}
    };
    cout << "Path 0->1->2: 4 + (-5) = -1, Direct 2->0: 2\n";
    vector<vector<int>> result7 = floydWarshall(graph7, 3);
    printMatrix(result7, 3, "Test 7");
    
    // Test 8: All pairs reachability test
    cout << "Test 8: Chain graph (testing transitivity)\n";
    vector<vector<int>> graph8 = {
        {0, 1, INF, INF, INF},
        {INF, 0, 1, INF, INF},
        {INF, INF, 0, 1, INF},
        {INF, INF, INF, 0, 1},
        {INF, INF, INF, INF, 0}
    };
    cout << "Chain: 0->1->2->3->4, testing all shortest paths\n";
    vector<vector<int>> result8 = floydWarshall(graph8, 5);
    printMatrix(result8, 5, "Test 8");
}

int main() {
    testFloydWarshall();
    return 0;
}
