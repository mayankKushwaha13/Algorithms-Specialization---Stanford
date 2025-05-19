/*
 * File Name    : Kosaraju.cpp
 *
 * Credit       : Course     - Graph Search, Shortest Paths, and Data Structures, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-05-19
 *
 * Description  : Implementation of Kosaraju Algorithm for finding Strongly Connected Components in a graph.
 */
#include <bits/stdc++.h>

using namespace std;

int t = 0;
int s = NULL;
vector < int > leader;
vector <pair<int,int> > finishingTime;
vector<bool> explored;
void DFS(vector < vector < int >> & g, int i) {
    explored[i] = true;
    leader[i] = s;
    for (auto v: g[i]) {
        if (!explored[v]) {
            DFS(g, v);
        }
    }
    t++;
    finishingTime[i].first = t;
    finishingTime[i].second = i;
}
void DFS_Loop(vector < vector < int >> & g) {
    int n = g.size() - 1;
    explored.assign(n + 1, false);
    leader.resize(n + 1);
    finishingTime.resize(n + 1);
    for (int i = n; i >= 0; i--) {
        if (!explored[i]) {
            s = i;
            DFS(g, i);
        }
    }
}
vector < vector < int >> KosarajuSCC(vector < vector < int >> & g) {
    int n = g.size();
    vector < vector < int >> grev(n);
    for (int u = 0; u < n; u++) {
        for (int v: g[u]) {
            grev[v].push_back(u);
        }
    }
    DFS_Loop(grev);
    t = 0;
    explored.assign(n, false);
    leader.assign(n, 0);
    sort(finishingTime.begin(), finishingTime.end());
    for (int i = n - 1; i >= 0; i--){
        int v = finishingTime[i].second;
        if(!explored[v]){
            s = v;
            DFS(g, v);
        }
    }
    vector < vector < int >> scc;
    // for (int i = 0; i < n; i++){
    //     scc[leader[i]].push_back(i);
    // }
    unordered_map < int, vector < int >> mpp;
    for (int i = 0; i < n; i++) {
        mpp[leader[i]].push_back(i);
    }
    for (auto & it: mpp) {
        scc.push_back(it.second);
    }

    return scc;
}
int main() {
    vector < vector < int >> graph(5);
    graph[0].push_back(1); // 0 → 1
    graph[1].push_back(3); // 1 → 3
    graph[2].push_back(0); // 2 → 0
    graph[3].push_back(4); // 3 → 4
    graph[4].push_back(1); // 4 → 1
    // graph[4].push_back(2); // 4 → 2

    vector < vector < int >> sccs = KosarajuSCC(graph);
    cout << "Strongly Connected Components :" << endl;
    for (int i = 0; i < sccs.size(); i++) {
        cout << "SCC " << i + 1 << " : ";
        for (int node: sccs[i]) {
            cout << node << " ";
        }
        cout << endl;
    }
}