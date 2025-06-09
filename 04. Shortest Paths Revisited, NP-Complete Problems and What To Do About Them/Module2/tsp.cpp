/*
 * File Name    : tsp.cpp
 *
 * Credit       : Course     - Shortest Paths Revisited, NP-Complete Problems and What To Do About Them, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-06-08
 *
 * Description  : Travelling Salesman Problem using DP
 */

#include <bits/stdc++.h>
using namespace std;

int tsp(set<int> &visited, vector<vector<int>> &dist, int current)
{
    int n = dist.size();
    if (visited.size() == n)
    {
        return dist[current][0];
    }

    int minCost = INT_MAX;

    for (int city = 0; city < n; city++)
    {
        if (visited.find(city) == visited.end())
        {                        
            visited.insert(city); 

            int cost = dist[current][city] + tsp(visited, dist, city);
            minCost = min(minCost, cost);

            visited.erase(city);
        }
    }

    return minCost;
}

int main()
{
    int n = 4;
    vector<vector<int>> dist = {
        {0, 20, 42, 25},
        {20, 0, 30, 34},
        {42, 30, 0, 10},
        {25, 34, 10, 0}};
    set<int> visited;
    visited.insert(0);
    cout << tsp(visited, dist, 0) << endl;
    return 0;
}
