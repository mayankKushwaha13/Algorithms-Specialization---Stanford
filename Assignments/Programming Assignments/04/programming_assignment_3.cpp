/*
 * File Name    : programming_assignment_3.cpp
 *
 * Credit       : Course     - Shortest Paths Revisited, NP-Complete Problems and What To Do About Them, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-06-10
 *
 * Description  : Programming Assignment 3 of Module 3
 */

/* TSP with nearest neighbour heuristic. */

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    ifstream testcase("../../test_cases/04/nn.txt");
    testcase >> n;
    
    vector<pair<double, double>> cities(n);
    int index;
    double x, y;
    
    for (int i = 0; i < n; i++) {
        testcase >> index >> x >> y;
        cities[index - 1] = {x, y};  
    }
    
    vector<bool> visited(n, false);
    double total = 0.0;
    int current = 0;
    visited[0] = true;
    
    for (int step = 0; step < n - 1; step++) {
        double mn = DBL_MAX;
        int next = -1;
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                double dx = cities[current].first - cities[i].first;
                double dy = cities[current].second - cities[i].second;
                double dist = sqrt(dx * dx + dy * dy);
                
                if (dist < mn || (dist == mn && i < next)) {
                    mn = dist;
                    next = i;
                }
            }
        }
        
        total += mn;
        visited[next] = true;
        current = next;
    }
    
    double dx = cities[current].first - cities[0].first;
    double dy = cities[current].second - cities[0].second;
    total += sqrt(dx * dx + dy * dy);
    
    cout << (long long)floor(total) << endl;
    return 0;
}
