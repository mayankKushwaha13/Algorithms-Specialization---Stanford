/*
 * File Name    : programming_assignment_3.cpp
 *
 * Credit       : Course     - Greedy Algorithms, Minimum Spanning Trees, and Dynamic Programming, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-06-05
 *
 * Description  : Programming Assignment 3 of Course 3
 */

#include <bits/stdc++.h>
using namespace std;
class Compare
{
public:
    bool operator()(pair<int, pair<int,int>> p1, pair<int, pair<int,int>> p2)
    {
        return p1.first > p2.first;
    }
};
pair<int, int> huffman(vector<int> &input)
{
    priority_queue<pair<int, pair<int,int>>, vector<pair<int, pair<int,int>>>, Compare> p;
    int n = input.size();
    if (n == 1) return {1, 1};
    for (int i = 0; i < n; i++)
    {
        p.push({input[i], {0,0}});
    }
    int mx = 0;
    int mn = INT_MAX;
    while (p.size() > 1)
    {
        pair<int, pair<int,int>> p1 = p.top();
        p.pop();
        pair<int, pair<int,int>> p2 = p.top();
        p.pop();
        int newFreq = (p1.first + p2.first);
        int newLevel = max(p1.second.first, p2.second.first) + 1;
        int newlevel = min(p1.second.second, p2.second.second) + 1;
        if(p1.second.second == p2.second.second) mn = newlevel;
        else mn = min(mn, newlevel);
        mx = max(mx, newLevel);
        p.push({newFreq, {newLevel, newlevel}});

    }

    return {mn, mx};
}
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
            s.emplace_back(i - 1);
            i -= 2;
        }
    }
    return s;
}
bool binarysearch(vector<int> &a, int l, int h, int k)
{
    int m = l + (h - l) / 2;
    while (l <= h)
    {

        if (a[m] == k)
        {
            return true;
        }
        else if (a[m] > k)
        {
            h = m - 1;
            m = l + (h - l) / 2;
        }
        else
        {
            l = m + 1;
            m = l + (h - l) / 2;
        }
    }
    return false;
}
int main()
{
    ifstream testcase1("../../test_cases/03/huffman.txt");
    ifstream testcase2("../../test_cases/03/mwis.txt");
    if (!testcase1.is_open())
    {
        cout << "File 1 could not be opened";
        return 0;
    }
    if (!testcase2.is_open())
    {
        cout << "File 2 could not be opened";
        return 0;
    }

    int n;
    testcase1 >> n;
    vector<int> g;
    int x;
    while (testcase1 >> x)
    {
        g.emplace_back(x);
    }
    pair<int, int> ans = huffman(g);
    cout << ans.first << " " << ans.second << endl;

    testcase2 >> n;
    vector<int> a(n + 1, 0);
    int i = 0;
    while (testcase2 >> x)
    {
        a[i++] = x;
    }
    auto ans2 = WIS(a);
    sort(ans2.begin(), ans2.end());
    vector<int> findthese = {1, 2, 3, 4, 17, 117, 517, 997};
    vector<bool> found(8, false);
    for (int i = 0; i < 8; i++)
    {
        found[i] = binarysearch(ans2, 0, ans2.size() - 1, findthese[i]-1);
    }
    for (bool x : found)
    {
        if (x)
            cout << 1;
        else
            cout << 0;
    }
}
