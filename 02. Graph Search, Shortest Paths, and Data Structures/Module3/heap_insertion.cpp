/*
 * File Name    : heap_insertion.cpp
 *
 * Credit       : Course     - Graph Search, Shortest Paths, and Data Structures, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-05-26
 *
 * Description  : Implementation of Insert and Bubble Up in a Min Heap
 */
#include <bits/stdc++.h>

using namespace std;

class MinHeap
{
private:
    vector<int> heap;
    int heapSize = 0;

    int parent(int i)
    {
        return (i - 1) / 2;
    }

    int leftChild(int i)
    {
        return 2 * i + 1;
    }

    int rightChild(int i)
    {
        return 2 * i + 2;
    }

    void bubbleUp(int index)
    {
        while (index > 0)
        {
            int parentIndex = parent(index);

            if (heap[parentIndex] <= heap[index])
                break;

            swap(heap[index], heap[parentIndex]);
            index = parentIndex;
        }
    }

public:
    MinHeap()
    {
        heap.reserve(100);
    }

    void insert(int key)
    {
        heap.push_back(key);
        heapSize++;

        bubbleUp(heapSize - 1);
    }

    void printHeap()
    {
        cout << "Heap contents: ";
        for (int i = 0; i < heapSize; i++)
        {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    MinHeap minHeap;

    minHeap.insert(4);
    minHeap.insert(1);
    minHeap.insert(3);
    minHeap.insert(2);
    minHeap.insert(16);
    minHeap.insert(9);
    minHeap.insert(10);
    minHeap.insert(14);

    minHeap.printHeap();
}