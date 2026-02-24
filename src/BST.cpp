#include "BST.hpp"
#include <algorithm>

BSTNode::BSTNode(std::string k, Product* p) : key(k), left(nullptr), right(nullptr) {
    products.push_back(p);
}

BST::BST() : root(nullptr) {}

void BST::insertRecursive(BSTNode*& node, Product* p) {
    if (!node) { node = new BSTNode(p->getName(), p); return; }
    if (p->getName() < node->key) insertRecursive(node->left, p);
    else if (p->getName() > node->key) insertRecursive(node->right, p);
    else node->products.push_back(p);
}

void BST::insert(Product* p) { insertRecursive(root, p); }

void BST::inorderRecursive(BSTNode* node, std::vector<Product*>& list) const {
    if (!node) return;
    inorderRecursive(node->left, list);
    for (auto p : node->products) list.push_back(p);
    inorderRecursive(node->right, list);
}

std::vector<Product*> BST::getAllSorted() const {
    std::vector<Product*> list;
    inorderRecursive(root, list);
    return list;
}

void BST::removeProductFromNode(BSTNode* node, Product* p) {
    if (!node) return;
    if (p->getName() < node->key) removeProductFromNode(node->left, p);
    else if (p->getName() > node->key) removeProductFromNode(node->right, p);
    else {
        auto it = std::find(node->products.begin(), node->products.end(), p);
        if (it != node->products.end()) node->products.erase(it);
    }
}

void BST::remove(Product* p) { removeProductFromNode(root, p); }

BSTNode* BST::findNode(BSTNode* node, const std::string& name) const {
    if (!node) return nullptr;
    if (name == node->key) return node;
    return (name < node->key) ? findNode(node->left, name) : findNode(node->right, name);
}

std::vector<Product*> BST::search(const std::string& name) const {
    BSTNode* n = findNode(root, name);
    return n ? n->products : std::vector<Product*>();
}