/*
 * File Name    : programming_assignment_1.cpp
 *
 * Credit       : Course     - Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-06-03
 *
 * Description  : Programming Assignment 1
 */
#include <bits/stdc++.h>
using namespace std;
bool comparator1(pair<int, int> p1, pair<int, int> p2){
    if (p1.first - p1.second > p2.first - p2.second) return true;
    if (p1.first - p1.second == p2.first - p2.second) return p1.first > p2.first;
    return false;
}
bool comparator2(pair<int, int> p1, pair<int, int> p2){
    if ((double)p1.first / (double)p1.second >= (double)p2.first / (double)p2.second) return true;
    return false;
}
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
                pq.push({edgeWeight, {v, u}});
            }
        }
    }
    
    return T;
}

int main()
{
    ifstream testcase("../../test_cases/03/jobs.txt");

    if (!testcase.is_open())
    {
        cout << "File could not be opened" << endl;
        return 0;
    }

    int m;
    testcase >> m;
    vector<pair<int, int>> v;
    int x;
    int i = 0;
    pair<int, int> p;
    while (testcase >> x)
    {
        if (i == 0)
            p.first = x;
        else
        {
            p.second = x;
            v.push_back(p);
        }
        i++;
        i %= 2;
    }

    sort(v.begin(), v.end(), comparator1);
    long long c = 0;
    long long sum = 0;
    for (auto p : v){
        c += p.second;
        sum += c * p.first;
    }
    cout << sum << endl;
    sort(v.begin(), v.end(), comparator2);
    c = 0;
    sum = 0;
    for (auto p : v){
        c += p.second;
        sum += c * p.first;
    }
    cout << sum << endl;

    ifstream testcase2("../../test_cases/03/edges.txt");

    if (!testcase2.is_open()){
        cout << "File 2 could not be opened" << endl;
        return 0;
    }

    int n, e;
    testcase2 >> n >> e;
    Graph g(n + 1);
    pair<pair<int, int>, int> p2;
    i = 0;
    while (testcase2 >> x)
    {
        if (i == 0)
            p2.first.first = x;
        else if (i == 1) p2.first.second = x;
        else
        {
            p2.second = x;
            g.addEdge(p2.first.first, p2.first.second, p2.second);
        }
        i++;
        i %= 3;
    }

    auto mst = primFast(g,1);
    long long totalWeight = 0;
    for (auto &edge : mst)
    {
        totalWeight += edge.first;
    }
    cout << totalWeight << endl;
}

