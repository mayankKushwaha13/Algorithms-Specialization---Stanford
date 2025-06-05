/*
 * File Name    : WIS.cpp
 *
 * Credit       : Course     - Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-06-05
 *
 * Description  : Max Weight Independent State implementation using dynamic programming
 */

#include<bits/stdc++.h>
using namespace std;
vector<int> WIS(vector<int> &g){
    vector<int> s;
    int n = g.size();
    vector<int> a(n + 1);
    a[0] = 0;
    a[1] = g[0];
    for(int i = 2; i <= n; i++){
        a[i] = max(a[i - 1], a[i - 2] + g[i - 1]);
    }
    int i = g.size();
    while(i >= 1){
        if(a[i - 1] >= a[i - 2] + g[i - 1] && i != 1) i--;
        else{
            s.emplace_back(g[i - 1]);
            i -= 2;
        }
    }
    return s;
}
int main(){
    vector<int> G = {1,4,5};
    auto ans = WIS(G);
    for (auto x : ans){
        cout << x << " ";
    }
}
