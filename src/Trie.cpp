#include "Trie.hpp"
char Trie::toLower(char c)
{
    return std::tolower(c);
}

void Trie::collectAll(TrieNode *node, vector<Product *> &results)
{
    if (!node)
        return;
    if (node->isEndOfWord && node->product != nullptr)
    {
        results.push_back(node->product);
    }
    for (auto pair : node->children)
    {
        collectAll(pair.second, results);
    }
}

bool Trie::removeHelper(TrieNode *node, string word, int depth)
{
    if (!node)
        return false;

    if (depth == word.size())
    {
        if (node->isEndOfWord)
        {
            node->isEndOfWord = false;
            node->product = nullptr;
            return node->children.empty();
        }
        return false;
    }

    char ch = toLower(word[depth]);
    if (node->children.find(ch) == node->children.end())
        return false;

    bool shouldDeleteChild = removeHelper(node->children[ch], word, depth + 1);

    if (shouldDeleteChild)
    {
        delete node->children[ch];
        node->children.erase(ch);
        return !node->isEndOfWord && node->children.empty();
    }

    return false;
}

Trie::Trie()
{
    root = new TrieNode();
}

void Trie::insert(Product *p)
{
    if (!p)
        return;
    TrieNode *curr = root;
    string name = p->getName();
    for (char c : name)
    {
        char ch = toLower(c);
        if (curr->children.find(ch) == curr->children.end())
        {
            curr->children[ch] = new TrieNode();
        }
        curr = curr->children[ch];
    }
    curr->isEndOfWord = true;
    curr->product = p;
}

void Trie::remove(string name)
{
    removeHelper(root, name, 0);
}

vector<Product *> Trie::searchPrefix(string prefix)
{
    vector<Product *> results;
    TrieNode *curr = root;

    for (char c : prefix)
    {
        char ch = toLower(c);
        if (curr->children.find(ch) == curr->children.end())
        {
            return results;
        }
        curr = curr->children[ch];
    }

    collectAll(curr, results);
    return results;
}