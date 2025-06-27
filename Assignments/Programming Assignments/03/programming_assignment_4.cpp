/*
 * File Name    : programming_assignmen_4.cpp
 *
 * Credit       : Course     - Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-06-06
 *
 * Description  : Programming Assignment 4 of Couorse 3
 */

#include<bits/stdc++.h>
using namespace std;
long long knapsack(vector<int> &weights, vector<int> &values, int W) {
    int n = weights.size();
    vector<long long> dp(W + 1, 0); 
    
    for (int i = 0; i < n; i++) {
        for (int j = W; j >= weights[i]; j--) {
            dp[j] = max(dp[j], dp[j - weights[i]] + values[i]);
        }
    }
    return dp[W];
}

int main(){
    ifstream testcase1("../../test_cases/03/knapsack1.txt");
    ifstream testcase2("../../test_cases/03/knapsack_big.txt");
    if(!testcase1.is_open()){
        cout << "File 1 could not be opened";
        return 0;
    }
    if(!testcase2.is_open()){
        cout << "File 2 could not be opened";
        return 0;
    }
    int W, n;
    testcase1 >> W >> n;
    vector<int> weights(n);
    vector<int> values(n);
    int i = 0;
    while(testcase1 >> values[i] >> weights[i]){
        i++;
    }
    cout << knapsack(weights, values, W) << endl;

    testcase2 >> W >> n;
    weights.resize(n);
    values.resize(n);
    i = 0;
    while(testcase2 >> values[i] >> weights[i]){
        i++;
    }

    cout << knapsack(weights, values, W) << endl;
}
