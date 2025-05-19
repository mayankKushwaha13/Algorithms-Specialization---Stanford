/*
 * File Name    : programming_assignment_1.cpp
 *
 * Credit       : Course     - Graph Search, Shortest Paths, and Data Structures, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-05-19
 *
 * Description  : Programming Assignment 1 of 2.1
 */

#include <bits/stdc++.h>
using namespace std;

int t = 0;
int s = -1;
vector<int> leader;
vector<pair<int, int>> finishingTime;
vector<bool> explored;

void DFS(vector<vector<int>> &g, int start) {
    stack<int> stk;
    stk.push(start);
    explored[start] = true;
    leader[start] = s;
    while (!stk.empty()) {
        int v = stk.top();
        bool allProcessed = true;
        
        for (int neighbor : g[v]) {
            if (!explored[neighbor]) {
                explored[neighbor] = true;
                leader[neighbor] = s;
                stk.push(neighbor);
                allProcessed = false;
            }
        }
        
        if (allProcessed) {
            stk.pop();
                t++;
                finishingTime[v] = {t, v};
        }
    }
}

void DFS_Loop(vector<vector<int>> &g) {
    int n = g.size() - 1;
    explored.assign(n + 1, false);
    leader.resize(n + 1, 0);
    finishingTime.resize(n + 1, {0, 0});
    
    for (int i = n; i > 0; i--) {
        if (!explored[i]) {
            s = i;
            DFS(g, i);
        }
    }
}

vector<vector<int>> KosarajuSCC(vector<vector<int>> &g) {
    int n = g.size();
    
    vector<vector<int>> grev(n);
    for (int u = 1; u < n; u++) {
        for (int v : g[u]) {
            grev[v].push_back(u);
        }
    }
    
    DFS_Loop(grev);
    
    vector<pair<int, int>> validFinishing;
    for (int i = 1; i < n; i++) {
        if (finishingTime[i].first > 0) {
            validFinishing.push_back(finishingTime[i]);
        }
    }
    sort(validFinishing.begin(), validFinishing.end(), greater<pair<int, int>>());
    
    t = 0;
    explored.assign(n, false);
    leader.assign(n, 0);
    
    for (auto &p : validFinishing) {
        int v = p.second;
        if (!explored[v]) {
            s = v;
            DFS(g, v);
        }
    }
    
    unordered_map<int, vector<int>> mpp;
    for (int i = 1; i < n; i++) {
        if (leader[i] > 0) {
            mpp[leader[i]].push_back(i);
        }
    }
    
    vector<vector<int>> scc;
    for (auto &it : mpp) {
        scc.push_back(it.second);
    }
    
    return scc;
}

int main() {
    ifstream testcase("../../test_cases/02/SCC.txt");
    if (!testcase.is_open()) {
        cout << "File failed to open";
        return 0;
    }
    
    int x, y, max_vertex = 0;
    while (testcase >> x >> y) {
        max_vertex = max(max_vertex, max(x, y));
    }
    testcase.clear();
    testcase.seekg(0);
    
    vector<vector<int>> g(max_vertex + 1);
    while (testcase >> x >> y) {
        g[x].push_back(y);
    }
    
    vector<vector<int>> sccs = KosarajuSCC(g);
    
    vector<int> sizes;
    for (auto &x : sccs) {
        sizes.push_back(x.size());
    }
    sort(sizes.begin(), sizes.end(), greater<int>());
    
    for (int i = 0; i < 5; i++) {
        cout << sizes[i];
        if (i < 4) cout << ",";
    }
    cout << endl;
}
