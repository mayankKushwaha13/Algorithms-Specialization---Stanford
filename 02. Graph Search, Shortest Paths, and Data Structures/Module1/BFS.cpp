/*
 * File Name    : BFS.cpp
 *
 * Credit       : Course     - Graph Search, Shortest Paths, and Data Structures, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-05-16
 *
 * Description  : Implementation of BFS
 */

#include <bits/stdc++.h>
using namespace std;

void BFS(vector<vector<int>>& g, int s,vector<bool> &visited, int componentID){
    int n = g.size();
    vector<int> dist(g.size(),-1);
    dist[s] = 0;
    visited[s] = true;
    queue<int> Q;
    Q.push(s);
    while(!Q.empty()){
        int v = Q.front();
        Q.pop();
        cout << "Visiting Node " << v << " (Distance : " << dist[v] << ")" <<endl;
        for (int neighbor : g[v]){
            if(!visited[neighbor]){
                visited[neighbor] = true;
                Q.push(neighbor);
                dist[neighbor] = dist[v] + 1;
            }
        }
    }
    
    
}
void findConnectedComponents(vector<vector<int>> &g){
    int n = g.size();
    int componentCount = 0;
    vector<bool> visited(n, false);
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            BFS(g, i,visited,componentCount);
            componentCount++;
        }
    }
    
    cout << "Total connected components: " << componentCount << endl;
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
    findConnectedComponents(G);
    cout << "\nTesting with a disconnected graph:" << endl;
    vector<vector<int>> disconnectedG = {
        {1, 3},     // Component 1
        {0, 2},  
        {1},     
        {0},     
        
        {5, 6},     // Component 2
        {4},
        {4},
        
        {8},        // Component 3
        {7}
    };
    findConnectedComponents(disconnectedG);
}
