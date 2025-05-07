/*
 * File Name    : merge_sort.cpp
 *
 * Credit       : Course     - Divide and Conquer, Sorting and Searching, and Randomized Algorithms, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-05-07
 *
 * Description  : Implementation of Merge Sort
 */

#include <bits/stdc++.h>

using namespace std;

void merge(int arr[], int temp[], int low, int mid, int high) {
    int i = low;
    int j = mid;
    int k = low;
    while (i < mid && j <= high) {
        if (arr[i] < arr[j]) {
            temp[k] = arr[i];
            i++;
            k++;
        }
        else {
            temp[k] = arr[j];
            j++;
            k++;
        }
    }
    while (i < mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }
    while (j <= high) {
        temp[k] = arr[j];
        j++;
        k++;
    }
    for (int i = low; i < high + 1; i++) {
        arr[i] = temp[i];
    }
}
void mergeSort(int arr[], int temp[], int low, int high) {
    if (low >= high) return;
    int mid = low + (high - low) / 2;
    mergeSort(arr, temp, low, mid);
    mergeSort(arr, temp, mid + 1, high);
    merge(arr, temp, low, mid + 1, high);
}
int main() {
    int n;
    cin >> n;
    int a[n], b[n];
    for (int i = 0; i < n; i++) cin >> a[i];
    mergeSort(a, b, 0, n - 1);
    for (int i = 0; i < n; i++) cout << a[i] << " ";
}