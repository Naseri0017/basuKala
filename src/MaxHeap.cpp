#include "MaxHeap.hpp"
#include <algorithm>

void MaxHeap::heapifyUp(int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;
        if (heap[index]->getSold() <= heap[parent]->getSold())
            break;
        std::swap(heap[index], heap[parent]);
        index = parent;
    }
}

void MaxHeap::heapifyDown(int index)
{
    int size = heap.size();
    while (true)
    {
        int largest = index, left = 2 * index + 1, right = 2 * index + 2;
        if (left < size && heap[left]->getSold() > heap[largest]->getSold())
            largest = left;
        if (right < size && heap[right]->getSold() > heap[largest]->getSold())
            largest = right;
        if (largest == index)
            break;
        std::swap(heap[index], heap[largest]);
        index = largest;
    }
}

void MaxHeap::insert(Product *p)
{
    heap.push_back(p);
    heapifyUp(heap.size() - 1);
}

void MaxHeap::remove(Product *p)
{
    auto it = std::find(heap.begin(), heap.end(), p);
    if (it != heap.end())
    {
        std::swap(*it, heap.back());
        heap.pop_back();
        if (it != heap.end())
        {
            int idx = std::distance(heap.begin(), it);
            heapifyDown(idx);
            heapifyUp(idx);
        }
    }
}

void MaxHeap::update(Product *p)
{
    auto it = std::find(heap.begin(), heap.end(), p);
    if (it != heap.end())
        heapifyUp(std::distance(heap.begin(), it));
}

Product *MaxHeap::getTop() const { return heap.empty() ? nullptr : heap[0]; }