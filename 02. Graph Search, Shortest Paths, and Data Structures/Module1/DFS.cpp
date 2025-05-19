/*
 * File Name    : DFS.cpp
 *
 * Credit       : Course     - Graph Search, Shortest Paths, and Data Structures, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-05-18
 *
 * Description  : Implementation of Depth First Search
 */
#include <bits/stdc++.h>
using namespace std;

void DFS(vector<vector<int>> &g, int s){
    vector<bool> visited(g.size(), false);
    stack<int> S;
    visited[s] = true;
    S.push(s);
    while(!S.empty()){
        int v = S.top();
        S.pop();
        cout << v << " ";
        for (auto it = g[v].rbegin(); it != g[v].rend(); ++it){
            if (!visited[*it]){
                visited[*it] = true;
                S.push(*it);
            }
        }
    }
    cout << endl;
}
void DFS_Recursive(vector<vector<int>>& graph, int v, vector<bool>& visited) {
    visited[v] = true;
    cout << v << " ";
    for (int neighbor : graph[v]) {
        if (!visited[neighbor]) {
            DFS_Recursive(graph, neighbor, visited);
        }
    }
}

int main() {
    vector<vector<int>> G = {
        {1, 3},     // Node 0's neighbors
        {0, 2, 4},  // Node 1's neighbors
        {1, 5},     // Node 2's neighbors
        {0, 4},     // Node 3's neighbors
        {1, 3, 5},  // Node 4's neighbors
        {2, 4, 6},  // Node 5's neighbors
        {5}         // Node 6's neighbors
    };
    vector<bool> visited(G.size(), false);
    DFS(G, 0);
    DFS_Recursive(G, 0, visited);

}
