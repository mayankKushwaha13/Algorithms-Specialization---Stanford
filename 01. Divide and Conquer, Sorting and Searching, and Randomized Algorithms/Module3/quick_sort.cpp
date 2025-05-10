/*
 * File Name    : programming_assignment_3.cpp
 *
 * Credit       : Course     - Divide and Conquer, Sorting and Searching, and Randomized Algorithms, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-05-10
 *
 * Description  : Quick Sort Implementation
 */
#include <bits/stdc++.h>

using namespace std;
void quickSort(vector < int > & a, int l, int h) {
    if (l >= h) return;
    int pivot = a[l];
    int i = l + 1;
    for (int j = l + 1; j <= h; j++) {
        if (a[j] < pivot) {
            swap(a[j], a[i]);
            i++;
        }
    }
    swap(a[l], a[i - 1]);
    quickSort(a, l, i - 2);
    quickSort(a, i, h);
}
int main() {
    vector < int > a = {
        24,
        56,
        19,
        18,
        13,
        9,
        0,
        4
    };
    quickSort(a, 0, a.size() - 1);
    for (int i = 0; i < a.size(); i++) cout << a[i] << " ";
}