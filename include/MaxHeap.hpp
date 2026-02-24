#ifndef MAXHEAP_HPP
#define MAXHEAP_HPP

#include "Product.hpp"
#include <vector>

class MaxHeap {
private:
    std::vector<Product*> heap;
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    void insert(Product* p);
    void remove(Product* p);
    void update(Product* p);
    Product* getTop() const; 
};

#endif