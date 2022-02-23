#pragma once

#include <iostream>
#include <vector>

#include "word_score.h"

class Display
{
public:
    Display();
    ~Display(){};

    void add_guess(const std::string user_guess, const WordScore score);
    void update_display() const;

private:
    std::vector<WordScore> _game_state;
    std::vector<std::string> _guesses;
};