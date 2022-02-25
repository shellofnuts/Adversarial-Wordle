#pragma once

#include <memory>

#include "file_reader.h"
#include "opponent.h"
#include "display.h"

class Game
{
public:
    Game(std::string allowed_words, std::string answers);

    void play();

private:
    int MAX_GAME_ITERATIONS = 12;
    std::string get_input();
    void update_opponent(const std::string &user_input);
    void update_board(const std::string &user_input);
    bool end_condition() const;

    int current_iteration = 0;

    std::unique_ptr<Display> _internal_display;
    std::unique_ptr<WordList> _internal_word_list;
    std::unique_ptr<WordList> _internal_answers;
    std::unique_ptr<Opponent> _internal_opponent;
};