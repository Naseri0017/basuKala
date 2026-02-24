#ifndef BST_HPP
#define BST_HPP

#include "Product.hpp"
#include <vector>
#include <string>

struct BSTNode {
    std::string key;
    std::vector<Product*> products;
    BSTNode *left, *right;
    BSTNode(std::string k, Product* p);
};

class BST {
private:
    BSTNode* root;
    void insertRecursive(BSTNode*& node, Product* p);
    void inorderRecursive(BSTNode* node, std::vector<Product*>& list) const;
    void removeProductFromNode(BSTNode* node, Product* p);
    BSTNode* findNode(BSTNode* node, const std::string& name) const;

public:
    BST();
    void insert(Product* p);
    void remove(Product* p);
    std::vector<Product*> getAllSorted() const; 
    std::vector<Product*> search(const std::string& name) const;
};

#endif