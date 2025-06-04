/*
 * File Name    : k_clusters.cpp
 *
 * Credit       : Course     - Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-06-04
 *
 * Description  : Implementing K-clustering in c++ using kruskal's MST algorithm.
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

int kClusters(int n, vector<Edge>& edges, int k) {
    sort(edges.begin(), edges.end());
    UnionFind uf(n);

    for (const Edge& e : edges) {
        if (uf.cluster_count() == k)
            break;
        uf.unite(e.u, e.v);
    }

    unordered_map<int, vector<int>> clusters;
    for (int i = 0; i < n; ++i) {
        int root = uf.find(i);
        clusters[root].push_back(i);
    }
    cout << "Clusters:\n";
    int cluster_id = 1;
    for (const auto& pair : clusters) {
        cout << "Cluster " << cluster_id++ << ": ";
        for (int node : pair.second)
            cout << node << " ";
        cout << endl;
    }

    for (const Edge& e : edges) {
        if (uf.find(e.u) != uf.find(e.v)) {
            return e.weight;
        }
    }
    return -1; 
}

int main() {
    int n = 6;
    vector<Edge> edges = {
        {0, 1, 3}, {0, 4, 5}, {1, 2, 5}, {1, 4, 2},
        {2, 3, 3}, {2, 5, 7}, {3, 4, 6}, {3, 5, 2},
        {4, 5, 4}
    };

    int k = 3;
    int result = kClusters(n, edges, k);
    cout << result << endl;
    return 0;
}
