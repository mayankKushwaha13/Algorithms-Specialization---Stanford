/*
 * File Name    : programming_assignment_1.cpp
 *
 * Credit       : Course     - Shortest Paths Revisited, NP-Complete Problems and What To Do About Them, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-06-07
 *
 * Description  : Programming Assignment 1 of Course 4
 */
#include <bits/stdc++.h>
using namespace std;
#define INF INT_MAX
pair<vector<vector<int>>, int> floydWarshall(vector<vector<int>> &graph, int n)
{
    vector<vector<int>> dist(n, vector<int>(n));

    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            if (i == j)
                dist[i][j] = 0;
            else if (graph[i][j] != INF)
                dist[i][j] = graph[i][j];
            else
                dist[i][j] = INF;
        }
    }
    int mn = INT_MAX;
    for (int k = 1; k < n; k++)
    {
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j < n; j++)
            {
                if (dist[i][k] != INF && dist[k][j] != INF)
                {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    if (j != i)
                        mn = min(mn, dist[i][j]);
                }
            }
        }
    }
    for (int i = 1; i < n; i++)
    {
        if (dist[i][i] < 0)
        {
            cout << "Negative Edge Cycle Found" << endl;
            return {{}, mn};
        }
    }

    return {dist, mn};
}

int main()
{
    ifstream case1("../../test_cases/04/g1.txt");
    ifstream case2("../../test_cases/04/g2.txt");
    ifstream case3("../../test_cases/04/g3.txt");
    int V1, E1, V2, E2, V3, E3;
    case1 >> V1 >> E1;
    case2 >> V2 >> E2;
    case3 >> V3 >> E3;

    vector<vector<int>> g1(V1 + 1, vector<int>(V1 + 1, INF)), 
    g2(V2 + 1, vector<int>(V2 + 1, INF)), g3(V3 + 1, vector<int>(V3 + 1,INF));
    pair<int, pair<int, int>> p;
    int i = 0;
    int x;
    while (case1 >> x)
    {
        if (i == 0)
            p.first = x;
        else if (i == 1)
            p.second.first = x;
        else
        {
            p.second.second = x;
            g1[p.first][p.second.first] = p.second.second;
        }
        i++;
        i %= 3;
    }
    i = 0;
    while (case2 >> x)
    {
        if (i == 0)
            p.first = x;
        else if (i == 1)
            p.second.first = x;
        else
        {
            p.second.second = x;
            g2[p.first][p.second.first] = p.second.second;
        }
        i++;
        i %= 3;
    }
    i = 0;
    while (case3 >> x)
    {
        if (i == 0)
            p.first = x;
        else if (i == 1)
            p.second.first = x;
        else
        {
            p.second.second = x;
            g3[p.first][p.second.first] = p.second.second;
        }
        i++;
        i %= 3;
    }
    pair<vector<vector<int>>, int> p1 = floydWarshall(g1, V1 + 1);
    pair<vector<vector<int>>, int> p2 = floydWarshall(g2, V2 + 1);
    pair<vector<vector<int>>, int> p3 = floydWarshall(g3, V3 + 1);
    int mn = INT_MAX;
    if (p1.first.size() != 0)
    {
        mn = min(mn, p1.second);
    }
    if (p2.first.size() != 0)
    {
        mn = min(mn, p2.second);
    }
    if (p3.first.size() != 0)
    {
        mn = min(mn, p3.second);
    }
    cout << mn << endl;
}