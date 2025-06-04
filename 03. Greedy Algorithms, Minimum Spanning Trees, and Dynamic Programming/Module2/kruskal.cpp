/*
 * File Name    : kruskal.cpp
 *
 * Credit       : Course     - Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-06-04
 *
 * Description  : Kruskal's MST Algorithm Implementation using Union Find Data Structure
 */

#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int u, v, weight;
    bool operator<(const Edge &other) const
    {
        return weight < other.weight;
    }
};

class UnionFind
{
    vector<int> parent, size;

public:
    UnionFind(int n) : parent(n), size(n, 1)
    {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x)
    {
        int root = x;
        while (parent[root] != root)
        {
            root = parent[root];
        }
        while (parent[x] != root)
        {
            int next = parent[x];
            parent[x] = root; 
            x = next;
        }
        return root;
    }

    bool unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return false;

        if (size[x] < size[y])
            swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        return true;
    }

    bool same(int x, int y)
    {
        return find(x) == find(y);
    }
};

vector<Edge> kruskalMST(int n, vector<Edge> &edges)
{
    sort(edges.begin(), edges.end());
    UnionFind uf(n);
    vector<Edge> mst;
    for (const Edge &e : edges)
    {
        if (uf.unite(e.u, e.v))
        {
            mst.push_back(e);
            if (mst.size() == n - 1)
                break; 
        }
    }

    return mst;
}

int main()
{
    int n = 6;
    vector<Edge> edges = {
        {0, 1, 3}, {0, 4, 5}, {1, 2, 5}, {1, 4, 2}, {2, 3, 3}, {2, 5, 7}, {3, 4, 6}, {3, 5, 2}, {4, 5, 4}};

    vector<Edge> mst = kruskalMST(n, edges);

    cout << "Minimum Spanning Tree:\n";
    int totalWeight = 0;
    for (const Edge &e : mst)
    {
        cout << e.u << " -- " << e.v << " : " << e.weight << "\n";
        totalWeight += e.weight;
    }
    cout << "Total weight: " << totalWeight << "\n";

    return 0;
}
