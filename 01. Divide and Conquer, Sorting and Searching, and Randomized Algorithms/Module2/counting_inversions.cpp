/*
 * File Name    : counting_inversions.cpp
 *
 * Credit       : Course     - Divide and Conquer, Sorting and Searching, and Randomized Algorithms, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-05-08
 *
 * Description  : Program to count inversions in an array meaning for each i < j we find such pairs where a[i] > a[j] in a given array a
 */
#include <bits/stdc++.h>

using namespace std;
int merge_and_countSplitInv(int a[], int l, int m, int h) {
    int res = 0;
    int n1 = m - l + 1;
    int n2 = h - m;
    int left[n1], right[n2];
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
int sort_and_count(int a[], int l, int h) {
    int res = 0;
    if (l < h) {
        int m = l + (h - l) / 2;
        res += sort_and_count(a, l, m);
        res += sort_and_count(a, m + 1, h);
        res += merge_and_countSplitInv(a, l, m, h);
    }
    return res;
}
int main() {
    int a[] = {1,3,5,2,4,6,7,8};
    cout << sort_and_count(a, 0, 7);
}