/*
 * File Name    : knapsack_01.cpp
 *
 * Credit       : Course     - Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-06-06
 *
 * Description  : 0/1 Knapsack Problem using Dynamic Programming
 */

#include <bits/stdc++.h>
using namespace std;

int knapsack(vector<int> &weights, vector<int> &values, int W)
{
    int n = values.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 0; j < W + 1; j++)
        {
            dp[i][j] = dp[i - 1][j];
            if(j >= weights[i - 1]){
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weights[i - 1]] + values[i - 1]);
            }
        }
    }
    return dp[n][W];
}
int main()
{
    vector<int> weights = {4, 3, 2, 3}; // w1=4, w2=3, w3=2, w4=3
    vector<int> values = {3, 2, 4, 4};  // v1=3, v2=2, v3=4, v4=4
    int W = 6;                          // Knapsack capacity

    int result = knapsack(weights, values, W);

    cout << "Weights: ";
    for (int w : weights)
        cout << w << " ";
    cout << "\nValues:  ";
    for (int v : values)
        cout << v << " ";
    cout << "\nCapacity: " << W << endl;
    cout << "Maximum value: " << result << endl;
}