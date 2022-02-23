#include "trie_node.h"

Trie::Trie()
{   
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        _head.children[i] = NULL;
    }
    _head.is_word = false;
}

bool Trie::search(const std::string &word) const
{
    const TrieNode *crawl_ptr = &this->_head;

    for (auto &ch: word)
    {
        int index = ch - 'a';
        if(crawl_ptr->children[index] == NULL)
        {
            return false;
        }
        crawl_ptr = crawl_ptr->children[index].get();
    }
    return crawl_ptr->is_word;
}

bool Trie::insert(std::string word)
{
    TrieNode *crawl_ptr = &this->_head;
    for (auto &ch: word)
    {
        int index = ch - 'a';
        if(crawl_ptr->children[index] == NULL)
        {
            crawl_ptr->children[index] = create_node();
        }
        crawl_ptr = crawl_ptr->children[index].get();
    }
    crawl_ptr->is_word = true;
    return true;
}

std::unique_ptr<struct TrieNode> Trie::create_node()
{
    std::unique_ptr<struct TrieNode> node = std::make_unique<struct TrieNode>();
    node->children = { 0 };
    node->is_word = false;
    return node;
}