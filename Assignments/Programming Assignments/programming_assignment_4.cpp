/*
 * File Name    : programming_assignment_4.cpp
 *
 * Credit       : Course     - Divide and Conquer, Sorting and Searching, and Randomized Algorithms, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-05-16
 *
 * Description  : Computing min cut of graphs using Karger's Randomised Contraction Algorithm
 */
#include <bits/stdc++.h>
using namespace std;
int karger(map<int, vector<int>> mpp)
{

    while (mpp.size() > 2)
    {
         auto it = mpp.begin();
        int pos = rand() % mpp.size();
        while(pos--){
            it++;
        }
        int u = it->first;
        if (mpp[u].empty()) continue;
        int v = mpp[u][rand() % mpp[u].size()];
        mpp[u].insert(mpp[u].end(), mpp[v].begin(), mpp[v].end());
        mpp.erase(v);
        for (auto &it : mpp)
        {
            vector<int> newNeighbors;
            for (int neighbor : it.second)
            {
                if (neighbor == v)
                    newNeighbors.push_back(u);
                else
                    newNeighbors.push_back(neighbor);
            }
            it.second = newNeighbors;
        }
        vector<int> filtered;
        for (int neighbor : mpp[u])
        {
            if (neighbor != u)
                filtered.push_back(neighbor);
        }
        mpp[u] = filtered;
    }
    int edges = 0;
    for (auto it : mpp){
        edges += it.second.size();
    }
    return edges/2;
}
int main()
{
    ifstream testcase("../test_cases/01/karger.txt");
    if (!testcase.is_open())
    {
        cout << "File could not be opened.";
        return 0;
    }
    map<int, vector<int>> adjList;
    string line;
    while (getline(testcase, line))
    {
        if (line.empty())
            continue;
        stringstream ss(line);
        int vertex;
        ss >> vertex;
        vector<int> neighbors;
        int neighbor;
        while (ss >> neighbor)
        {
            neighbors.push_back(neighbor);
        }
        adjList[vertex] = neighbors;
    }
    int mincut = INT_MAX;
    int count = 200;
    while (count--)
    {
        mincut = min(mincut, karger(adjList));
    }
    cout << mincut << endl;
}