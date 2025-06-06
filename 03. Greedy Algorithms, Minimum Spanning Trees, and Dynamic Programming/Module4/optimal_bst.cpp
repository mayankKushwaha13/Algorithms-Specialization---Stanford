/*
 * File Name    : optimal_bst.cpp
 *
 * Credit       : Course     - Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-06-06
 *
 * Description  : Optimal BST implementation using DP
 */

#include<bits/stdc++.h>
using namespace std;


class OptimalBST{
public:
    double bst(vector<double> p){
        int n = p.size();
        vector<vector<double> > A(n+1, vector<double>(n, 0));   
        vector<vector<double> > P(n, vector<double>(n, 0));    
        vector<vector<int> > r(n, vector<int>(n, 0));          

        for(int i = 0; i < n; ++i)
        {
            P[i][i] = p[i];
            A[i][i] = p[i];
            r[i][i] = i;
        }

        for(int s = 1; s < n; ++s)
        {
            for(int i = 0; i+s < n; ++i)
            {
                P[i][i+s] = p[i] + P[i+1][i+s];

                double temp_min = 100000.0;
                for(int k = r[i][i+s-1]; k <= r[i+1][i+s]; ++k){
                    double temp = A[i][k-1] + A[k+1][i+s];
                    if(temp < temp_min)
                    {
                        temp_min = temp;
                        r[i][i+s] = k;
                    }
                }

                A[i][i+s] = P[i][i+s] + temp_min;
            }
        }
        return A[0][n-1];
    }
};

int main()
{
    double mydata[] = { 0.05, 0.4, 0.08, 0.04, 0.1, 0.1, 0.23 };
    vector<double> p(mydata, mydata + sizeof(mydata) / sizeof(double));

    OptimalBST optBST;
    double y = optBST.bst(p);

    cout<< y << endl;
    return 0;
}