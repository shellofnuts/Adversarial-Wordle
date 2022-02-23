#pragma once

#include <vector>
#include <array>
#include <memory>
#include <string>

const int ALPHABET_SIZE = 26;

struct TrieNode
{
    std::array<std::unique_ptr<struct TrieNode>, ALPHABET_SIZE> children;
    bool is_word;
};


class Trie
{
public:
    Trie();

    bool insert(const std::string word);
    bool search(const std::string &word) const;

private:
    std::unique_ptr<struct TrieNode> create_node();
    TrieNode _head;
};