/*
 * File Name    : topological_sort.cpp
 *
 * Credit       : Course     - Graph Search, Shortest Paths, and Data Structures, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-05-18
 *
 * Description  : Topological Sorting using DFS
 */
#include <bits/stdc++.h>

using namespace std;


void DFS(vector < vector < int >> & g, int s, vector < bool > & visited, int & current_label, vector < pair<int,int> > & topological_sort) {
    visited[s] = true;
    for (int v: g[s]) {
        if (!visited[v]) {
            DFS(g, v, visited, current_label, topological_sort);
        }
    }
    topological_sort.push_back({s, current_label--});
}
vector < pair<int, int> > DFS_Loop(vector < vector < int >> & g, vector < bool > & visited) {
    visited.assign(g.size(), false);
    vector < pair<int, int> > topological_sort;
    int current_label = g.size() - 1;
    for (int i = 0; i < g.size(); i++) {
        if (!visited[i]) {
            DFS(g, i, visited, current_label, topological_sort);
        }
    }
    reverse(topological_sort.begin(), topological_sort.end());
    return topological_sort;
}
int main() {
    vector<vector<int>> G = {
        {1, 2},     // Node 0 points to 1 and 2
        {3, 4},     // Node 1 points to 3 and 4
        {5, 6},     // Node 2 points to 5 and 6
        {7},        // Node 3 points to 7
        {7, 8},     // Node 4 points to 7 and 8
        {8},        // Node 5 points to 8
        {9},        // Node 6 points to 9
        {9},        // Node 7 points to 9
        {9},        // Node 8 points to 9
        {}          // Node 9 has no outgoing edges
    };
    vector < bool > visited(G.size(), false);
    vector < pair<int,int> > sorted = DFS_Loop(G, visited);
    for (auto x: sorted) cout << "(" << x.first << ", " << x.second << ")" << endl;
}