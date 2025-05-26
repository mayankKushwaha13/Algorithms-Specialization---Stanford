/*
 * File Name    : heap_extraction.cpp
 *
 * Credit       : Course     - Graph Search, Shortest Paths, and Data Structures, Stanford University on Coursera
 *                Instructor - Tim Roughgarden, Professor
 *
 * Author       : Mayank Kushwaha
 * Created Date : 2025-05-26
 *
 * Description  : Implementation of Extract Min and Bubble Down in Min Heap
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
    void bubbleDown(int index)
    {
        while (true)
        {
            int smallest = index;
            int left = leftChild(index);
            int right = rightChild(index);

            if (left < heapSize && heap[left] < heap[smallest])
            {
                smallest = left;
            }

            if (right < heapSize && heap[right] < heap[smallest])
            {
                smallest = right;
            }

            if (smallest == index)
                break;

            swap(heap[index], heap[smallest]);
            index = smallest;
        }
    }

public:
    MinHeap()
    {
        heap.reserve(100);
    }

    bool isEmpty()
    {
        return heapSize == 0;
    }

    void insert(int key)
    {
        heap.push_back(key);
        heapSize++;

        bubbleUp(heapSize - 1);
    }
    void printHeap()
    {
        std::cout << "Heap contents: ";
        for (int i = 0; i < heapSize; i++)
        {
            std::cout << heap[i] << " ";
        }
        std::cout << std::endl;
    }

    int extractMin()
    {
        if (heapSize == 0)
        {
            throw std::runtime_error("Heap is empty");
        }

        int minVal = heap[0];

        heap[0] = heap[heapSize - 1];
        heapSize--;
        heap.pop_back();

        if (heapSize > 0)
        {
            bubbleDown(0);
        }

        return minVal;
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

    cout << "Extracting elements: ";
    while (!minHeap.isEmpty())
    {
        cout << minHeap.extractMin() << " ";
    }
    cout << endl;

    return 0;
}
