#ifndef HISTORY_HPP
#define HISTORY_HPP
#include <string>

struct HistoryNode {
    int orderId;
    std::string productList;
    unsigned long totalCost;
    HistoryNode* next;

    HistoryNode(int id, std::string list, unsigned long cost) 
        : orderId(id), productList(list), totalCost(cost), next(nullptr) {}
};


class HistoryList {
public:
    HistoryNode* head = nullptr;

    void add(int id, std::string list, unsigned long cost) {
        HistoryNode* newNode = new HistoryNode(id, list, cost);
        newNode->next = head;
        head = newNode;
    }

    ~HistoryList() {
        while(head) {
            HistoryNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};
#endif