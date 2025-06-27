/*
 * File Name    : programming_assignment_3.cpp
 *
 * Credit       : Course     - Divide and Conquer, Sorting and Searching, and Randomized Algorithms, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-05-10
 *
 * Description  : Programming Assignment of Module 3
 */
#include <bits/stdc++.h>

using namespace std;
int quickSort1(vector<int> &a, int l, int h)
{
    int comparisons = 0;
    if (l >= h)
        return comparisons;
    int pivot = a[l];
    int i = l + 1;
    for (int j = l + 1; j <= h; j++)
    {
        if (a[j] < pivot)
        {
            swap(a[j], a[i]);
            i++;
        }
    }
    comparisons += h - l;
    swap(a[l], a[i - 1]);
    comparisons += quickSort1(a, l, i - 2);
    comparisons += quickSort1(a, i, h);
    return comparisons;
}

int quickSort2(vector<int> &a, int l, int h)
{
    int comparisons = 0;
    if (l >= h)
        return comparisons;
    int pivot = a[h];
    swap(a[h], a[l]);
    int i = l + 1;
    for (int j = l + 1; j <= h; j++)
    {
        if (a[j] < pivot)
        {
            swap(a[j], a[i]);
            i++;
        }
    }
    comparisons += h - l;
    swap(a[l], a[i - 1]);
    comparisons += quickSort2(a, l, i - 2);
    comparisons += quickSort2(a, i, h);
    return comparisons;
}

int quickSort3(vector<int> &a, int l, int h)
{
    int comparisons = 0;
    if (l >= h)
        return comparisons;
    int m = l + (h  - l) /2 ;
    set<int> s;
    s.insert(a[l]);
    s.insert(a[m]);
    s.insert(a[h]);
    int pivoti = 0;
    auto it = s.begin();
    it++;
    if(*it == a[l]) pivoti = l;
    else if (*it == a[m]) pivoti = m;
    else pivoti = h;
    int pivot = a[pivoti];
    swap(a[pivoti],a[l]);
    int i = l + 1;
    for (int j = l + 1; j <= h; j++)
    {
        if (a[j] < pivot)
        {
            swap(a[j], a[i]);
            i++;
        }
    }
    comparisons += h - l;
    swap(a[l], a[i - 1]);
    comparisons += quickSort3(a, l, i - 2);
    comparisons += quickSort3(a, i, h);
    return comparisons;
}
int main()
{
    ifstream testcase("../../test_cases/01/quicksort.txt");
    if (!testcase.is_open())
    {
        cout << "File Failed To Open";
        return 0;
    }
    vector<int> a,b,c;
    int x;
    while (testcase >> x){
        a.push_back(x);
        b.push_back(x);
        c.push_back(x);
    }
    cout << quickSort1(a, 0, a.size() - 1) << endl;
    cout << quickSort2(b, 0, b.size() - 1) << endl;
    cout << quickSort3(c, 0, c.size() - 1) << endl;
}