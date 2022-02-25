#pragma once

#include <set>
#include <string>
#include <optional>

#include "trie_node.h"


class WordList
{
public:
    WordList(std::string filename);

    bool check_word(std::string word) const;
    const std::set<std::string> &get_word_list() const;
    void print_set() const;
private:
    bool add_word(const std::string &word);
    std::set<std::string> _available_word_list;
    Trie _word_checker; 
};