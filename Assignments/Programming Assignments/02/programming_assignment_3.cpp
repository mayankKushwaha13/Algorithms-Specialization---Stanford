/*
 * File Name    : programming_assignment_3.cpp
 *
 * Credit       : Course     - Graph Search, Shortest Paths, and Data Structures, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-05-28
 *
 * Description  : Programming Assignment 3 of Course 2
 */

#include <bits/stdc++.h>
using namespace std;
class MedianMaintainer
{
private:
    priority_queue<int, vector<int>> H_Low; 
    priority_queue<int, vector<int>, greater<int>> H_High;

public:
    void insert(int x)
    {
        if (H_Low.empty() || x <= H_Low.top())
        {
            H_Low.push(x);
        }
        else
        {
            H_High.push(x);
        }

        // Step 2: Rebalance if necessary
        if (H_Low.size() > H_High.size() + 1)
        {
            H_High.push(H_Low.top());
            H_Low.pop();
        }
        else if (H_High.size() > H_Low.size() + 1)
        {
            H_Low.push(H_High.top());
            H_High.pop();
        }
    }

    int getMedian()
    {
        if (H_Low.size() >= H_High.size())
        {
            return H_Low.top();
        }
        else
        {
            return H_High.top();
        }
    }
};

int main()
{
    ifstream testcase("../../test_cases/02/median.txt");
    MedianMaintainer median;
    int x;
    long sum = 0;
    while (testcase >> x)
    {
        median.insert(x);
        int m = median.getMedian();
        sum = (sum + m % 10000) % 10000;
    }
    cout << sum << endl;
}
