/*
 * File Name    : sequence_alignment.cpp
 *
 * Credit       : Course     - Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-06-06
 *
 * Description  : Sequence Alignment using Dynamic Programming (Needleman-Wunsch Algorithm)
 */
#include <bits/stdc++.h>
using namespace std;

int getMismatchPenalty(char a, char b)
{
    if (a == b)
        return 0;
    return 1;
}

int sequenceAlignment(const string &X, const string &Y, int gapPenalty,
                      string &alignedX, string &alignedY)
{

    int m = X.length();
    int n = Y.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; i++)
    {
        dp[i][0] = i * gapPenalty;
    }
    for (int j = 0; j <= n; j++)
    {
        dp[0][j] = j * gapPenalty;
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int matchCost = dp[i - 1][j - 1] + getMismatchPenalty(X[i - 1], Y[j - 1]);
            int gapXCost = dp[i - 1][j] + gapPenalty;
            int gapYCost = dp[i][j - 1] + gapPenalty;
            dp[i][j] = min({matchCost, gapXCost, gapYCost});
        }
    }

    alignedX = "";
    alignedY = "";

    int i = m, j = n;
    while (i > 0 && j > 0)
    {
        int matchCost = dp[i - 1][j - 1] + getMismatchPenalty(X[i - 1], Y[j - 1]);
        int gapXCost = dp[i - 1][j] + gapPenalty;
        int gapYCost = dp[i][j - 1] + gapPenalty;

        if (dp[i][j] == matchCost)
        {
            alignedX = X[i - 1] + alignedX;
            alignedY = Y[j - 1] + alignedY;
            i--;
            j--;
        }
        else if (dp[i][j] == gapXCost)
        {
            alignedX = X[i - 1] + alignedX;
            alignedY = "-" + alignedY;
            i--;
        }
        else
        {
            alignedX = "-" + alignedX;
            alignedY = Y[j - 1] + alignedY;
            j--;
        }
    }

    while (i > 0)
    {
        alignedX = X[i - 1] + alignedX;
        alignedY = "-" + alignedY;
        i--;
    }
    while (j > 0)
    {
        alignedX = "-" + alignedX;
        alignedY = Y[j - 1] + alignedY;
        j--;
    }

    return dp[m][n];
}

void testSequenceAlignment()
{
    string X, Y;
    string alignedX, alignedY;
    int gapPenalty = 2;

    cout << "=== Sequence Alignment Test Cases ===\n\n";

    X = "AGGGCT";
    Y = "AGGCA";

    cout << "Test Case 1:\n";
    cout << "X: " << X << "\n";
    cout << "Y: " << Y << "\n";
    cout << "Gap Penalty: " << gapPenalty << "\n";

    int penalty1 = sequenceAlignment(X, Y, gapPenalty, alignedX, alignedY);

    cout << "\nOptimal Alignment:\n";
    cout << "X: " << alignedX << "\n";
    cout << "Y: " << alignedY << "\n";
    cout << "Total Penalty: " << penalty1 << "\n\n";

    X = "AACAGTTACC";
    Y = "TAAGGTCA";

    cout << "Test Case 2:\n";
    cout << "X: " << X << "\n";
    cout << "Y: " << Y << "\n";
    cout << "Gap Penalty: " << gapPenalty << "\n";

    int penalty2 = sequenceAlignment(X, Y, gapPenalty, alignedX, alignedY);

    cout << "\nOptimal Alignment:\n";
    cout << "X: " << alignedX << "\n";
    cout << "Y: " << alignedY << "\n";
    cout << "Total Penalty: " << penalty2 << "\n\n";

    X = "ATCG";
    Y = "";

    cout << "Test Case 3 (Edge Case):\n";
    cout << "X: " << X << "\n";
    cout << "Y: (empty)\n";
    cout << "Gap Penalty: " << gapPenalty << "\n";

    int penalty3 = sequenceAlignment(X, Y, gapPenalty, alignedX, alignedY);

    cout << "\nOptimal Alignment:\n";
    cout << "X: " << alignedX << "\n";
    cout << "Y: " << alignedY << "\n";
    cout << "Total Penalty: " << penalty3 << "\n";
}

int main()
{
    testSequenceAlignment();
    return 0;
}
