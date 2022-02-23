#pragma once

#include <set>
#include <string>

#include "trie_node.h"


class WordList
{
public:
    WordList(std::string filename);

    bool check_word(const std::string &word) const;
    std::set<std::string> get_word_list() const;

    void print_set() const;
private:
    bool add_word(const std::string &word);    
    int sort_words();
    std::set<std::string> _available_word_list;
    Trie _word_checker; 
};