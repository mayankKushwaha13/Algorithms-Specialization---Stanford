/*
 * File Name    : programming_assignment_2.cpp
 *
 * Credit       : Course     - Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-06-04
 *
 * Description  : Programming Assignment 2 of Course 3
 */

#include <bits/stdc++.h>
using namespace std;
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class UnionFind {
    vector<int> parent;
    vector<int> rank;
    int num_clusters;

public:
    UnionFind(int n) : parent(n), rank(n, 1), num_clusters(n) {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y])
            swap(x, y);
        parent[y] = x;
        rank[x] += rank[y];
        num_clusters--;
        return true;
    }

    int cluster_count() const {
        return num_clusters;
    }
};

int maxSpacing(int n, vector<Edge>& edges, int k) {
    sort(edges.begin(), edges.end());
    UnionFind uf(n);

    for (const Edge& e : edges) {
        if (uf.cluster_count() == k)
            break;
        uf.unite(e.u, e.v);
    }
    for (const Edge& e : edges) {
        if (uf.find(e.u) != uf.find(e.v)) {
            return e.weight;
        }
    }
    return -1; 
}
int bitsToInt(const vector<int>& bits) {
    int val = 0;
    for (int b : bits) {
        val = (val << 1) | b;
    }
    return val;
}
int main()
{
    ifstream testcase1("../../test_cases/03/clustering1.txt");
    ifstream testcase2("../../test_cases/03/clustering_big.txt");
    if (!testcase1.is_open())
    {
        cout << "File 1 could not be opened" << endl;
        return 0;
    }
    if (!testcase2.is_open())
    {
        cout << "File 2 could not be opened" << endl;
        return 0;
    }

    int n;
    testcase1 >> n;
    vector<Edge> graph(n + 1);
    pair<pair<int, int>, int> p;
    int x;
    int i = 0;
    while (testcase1 >> x)
    {
        if (i == 0)
            p.first.first = x;
        else if (i == 1)
            p.first.second = x;
        else
        {
            p.second = x;
            Edge e = {p.first.first, p.first.second, p.second};
            graph.push_back(e);
        }
        i++;
        i %= 3;
    }
    int ans1 = maxSpacing(n + 1, graph, 4);
    cout << ans1 << endl;

    int bits = 0;
    testcase2 >> n >> bits;;

    vector<vector<int>> g(n);
    unordered_map<int, int> nodeMap; 

    for (int i = 0; i < n; i++) {
        g[i].resize(bits);
        int val = 0;
        for (int j = 0; j < bits; j++) {
            testcase2 >> g[i][j];
            val = (val << 1) | g[i][j];
        }
        nodeMap[val] = i;
    }

    UnionFind uf(n);

    for (int i = 0; i < n; ++i) {
        int original = bitsToInt(g[i]);
        
        if (nodeMap.count(original)) {
            uf.unite(i, nodeMap[original]);
        }

        for (int j = 0; j < bits; j++) {
            int modified = original ^ (1 << (bits - j - 1));
            if (nodeMap.count(modified)) {
                uf.unite(i, nodeMap[modified]);
            }
        }

        for (int j = 0; j < bits; j++) {
            for (int k = j + 1; k < bits; k++) {
                int modified = original ^ (1 << (bits - j - 1)) 
                             ^ (1 << (bits - k - 1));
                if (nodeMap.count(modified)) {
                    uf.unite(i, nodeMap[modified]);
                }
            }
        }
    }

    cout << uf.cluster_count() << endl;


}
