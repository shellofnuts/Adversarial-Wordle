#pragma once

#include <file_reader.h>
#include <word_score.h>

#include <iostream>
#include <map>

class Opponent
{
public:
    Opponent(const WordList &master_record);
    ~Opponent() {};

    const WordScore prune_words(const std::string user_guess);

    void print_word_set() const;
private:
    std::set<std::string> _word_set;
};
