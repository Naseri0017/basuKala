#ifndef TRIE_HPP
#define TRIE_HPP

#include "Product.hpp"
#include <vector>
#include <unordered_map>
#include <string>
#include <cctype> 

using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    Product* product; 
    bool isEndOfWord;

    TrieNode() {
        product = nullptr;
        isEndOfWord = false;
    }
};

class Trie {
private:
    TrieNode* root;

    char toLower(char c);

    void collectAll(TrieNode* node, vector<Product*>& results);

    bool removeHelper(TrieNode* node, string word, int depth);

public:
    Trie();
    void insert(Product* p);

    void remove(string name);

    vector<Product*> searchPrefix(string prefix);
};

#endif