#pragma once

#include <file_reader.h>
#include <word_score.h>

#include <iostream>
#include <map>

class Opponent
{
public:
    Opponent(const WordList &master_record);

    const WordScore prune_words(const std::string user_guess);
    WordScore get_previous_score() const { return _previous_score; };
    int get_previous_num_score() const;
    std::string get_random_word() const;
    void print_word_set() const;
private:
    std::vector<const std::string*> _word_set;
    WordScore _previous_score;
};
