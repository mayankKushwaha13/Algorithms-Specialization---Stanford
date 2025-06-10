/*
 * File Name    : programming_assignment_4.cpp
 *
 * Credit       : Course     - Shortest Paths Revisited, NP-Complete Problems and What To Do About Them, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-06-10
 *
 * Description  : Programming Assignment 4
 */

#include <bits/stdc++.h>
using namespace std;

const int MAX = 2000001;

vector<int> adj[MAX];
vector<int> adjInv[MAX];
bool visited[MAX];
bool visitedInv[MAX];
stack<int> s;
int scc[MAX];
int counter;

void resetAll(int n) {
    for (int i = 1; i <= 2 * n; i++) {
        adj[i].clear();
        adjInv[i].clear();
        visited[i] = false;
        visitedInv[i] = false;
        scc[i] = 0;
    }
    while (!s.empty()) s.pop();
    counter = 1;
}

void addEdges(int a, int b) {
    adj[a].push_back(b);
}

void addEdgesInv(int a, int b) {
    adjInv[b].push_back(a);
}

void addClause(int a, int b, int n) {
    int pos_a = (a > 0) ? a : (-a + n);
    int neg_a = (a > 0) ? (a + n) : (-a);
    int pos_b = (b > 0) ? b : (-b + n);
    int neg_b = (b > 0) ? (b + n) : (-b);
    
    addEdges(neg_a, pos_b);
    addEdgesInv(neg_a, pos_b);
    addEdges(neg_b, pos_a);
    addEdgesInv(neg_b, pos_a);
}

void dfs(int u) {
    if (visited[u]) return;
    visited[u] = true;
    
    for (int v : adj[u]) {
        dfs(v);
    }
    s.push(u);
}

void dfsInv(int u) {
    if (visitedInv[u]) return;
    visitedInv[u] = true;
    
    for (int v : adjInv[u]) {
        dfsInv(v);
    }
    scc[u] = counter;
}

bool solve2SAT(const string filename, int n) {
    resetAll(n);
    
    ifstream file(filename);
    int a, b;
    int temp;
    file >> temp;
    while (file >> a >> b) {
        addClause(a, b, n);
    }
    file.close();
    for (int i = 1; i <= 2 * n; i++) {
        if (!visited[i]) dfs(i);
    }
    
    while (!s.empty()) {
        int u = s.top();
        s.pop();
        if (!visitedInv[u]) {
            dfsInv(u);
            counter++;
        }
    }
    
    // Check satisfiability
    for (int i = 1; i <= n; i++) {
        if (scc[i] == scc[i + n]) {
            return false;
        }
    }
    return true;
}

int main() {
    string ans = "";
    
    for (int i = 1; i <= 6; i++) {
        string filename = "2sat" + to_string(i) + ".txt";
        
        ifstream file("../../test_cases/04/" + filename);
        int n;
        file >> n;
        file.close();
        
        bool satisfiable = solve2SAT("../../test_cases/04/" + filename, n);
        ans += (satisfiable ? "1" : "0");
    }
    
    cout << ans << endl;
    return 0;
}
