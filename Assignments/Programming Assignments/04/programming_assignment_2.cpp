/*
 * File Name    : programming_assignment_2.cpp
 *
 * Credit       : Course     - Shortest Paths Revisited, NP-Complete Problems and What To Do About Them, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-06-08
 *
 * Description  : Programming Assignment 2 of Course 4
 */

#include <bits/stdc++.h>
using namespace std;

double tsp(const vector<vector<double>>& dist, int mask, int s, const int VISITED_ALL, vector<vector<double>>& dp, int start) {
    int n = dist.size();
    if (mask == VISITED_ALL) return dist[s][start];
    if (dp[mask][s] >= 0) return dp[mask][s];
    double ans = 1e9;
    for (int city = 0; city < n; city++) {
        if ((mask & (1 << city)) == 0) {
            double newAns = dist[s][city] + tsp(dist, mask | (1 << city), city, VISITED_ALL, dp, start);
            ans = min(ans, newAns);
        }
    }
    return dp[mask][s] = ans;
}


int main()
{
    ifstream testcase("../../test_cases/04/tsp.txt");

    int n;
    testcase >> n;

    int VISITED_ALL = (1 << 13) - 1;
    vector<vector<double>> dist(13, vector<double>(13, 1e9));
    vector<pair<double, double>> points(n);
vector<vector<double>> dp1(1 << 13, vector<double>(13, -1));

vector<vector<double>> dp2(1 << 14, vector<double>(14, -1));

    for (int i = 0; i < n; i++)
    {
        testcase >> points[i].first >> points[i].second;
    }

    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            if (i != j)
            {
                double dx = points[i].first - points[j].first;
                double dy = points[i].second - points[j].second;
                dist[i][j] = sqrt(dx * dx + dy * dy);
            }
        }
    }
    double tsp1 = tsp(dist, 1 << 11, 11, VISITED_ALL,dp1, 11);
    vector<vector<double>> dist2(14, vector<double>(14, 1e9));
    for (int i = 11; i < 25; i++)
    {
        for (int j = 11; j < 25; j++)
        {
            if (i != j)
            {
                double dx = points[i].first - points[j].first;
                double dy = points[i].second - points[j].second;
                dist2[i - 11][j - 11] = sqrt(dx * dx + dy * dy);
            }
        }
    }
    VISITED_ALL = (1 << 14) - 1;
    double tsp2 = tsp(dist2, 1 << 0, 0, VISITED_ALL, dp2, 0);
    double connect = sqrt(
        (points[11].first - points[12].first) * (points[11].first - points[12].first) +
        (points[11].second - points[12].second) * (points[11].second - points[12].second));

    double total = tsp1 + tsp2 - 2 * connect;
    cout << fixed << setprecision(10) << tsp1 << endl;
    cout << fixed << setprecision(10) << tsp2 << endl;
    cout << fixed << setprecision(10) << connect << endl;
    cout << fixed << setprecision(10) << total << endl;

    return 0;
}
