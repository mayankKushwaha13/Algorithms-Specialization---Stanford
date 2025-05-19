/*
 * File Name    : programming_assignment_2.cpp
 *
 * Credit       : Course     - Divide and Conquer, Sorting and Searching, and Randomized Algorithms, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-05-08
 *
 * Description  : Programming Assignment of Module 2
 */

#include <bits/stdc++.h>

using namespace std;
long long merge_and_countSplitInv(vector<int>& a, int l, int m, int h) {
    long long res = 0;
    int n1 = m - l + 1;
    int n2 = h - m;
    vector<int> left(n1), right(n2);
    for (int i = 0; i < n1; i++) left[i] = a[i+l];
    for (int i = 0; i < n2; i++) right[i] = a[i+m+1];
    int i = 0, j = 0, k = l;
    while(i < n1 && j < n2){
        if (left[i] <= right[j]){
            a[k++] = left[i++];
        }
        else{
            a[k++] = right[j++];
            res += n1 - i;
        }
    }
    while(i < n1) a[k++] = left[i++];
    while(j < n2) a[k++] = right[j++];
    return res;
}
long long sort_and_count(vector<int>& a, int l, int h) {
    long long res = 0;
    if (l < h) {
        int m = l + (h - l) / 2;
        res += sort_and_count(a, l, m);
        res += sort_and_count(a, m + 1, h);
        res += merge_and_countSplitInv(a, l, m, h);
    }
    return res;
}
int main() {
    ifstream testcase("../test_cases/01/inversion.txt");
    if(!testcase.is_open())
    {
        cout << "File failed to open" << endl;
        return 0;
    }
    vector<int> a;
    int integer;

    while(testcase >> integer)
        a.push_back(integer);
    cout << sort_and_count(a, 0, a.size() - 1);
}