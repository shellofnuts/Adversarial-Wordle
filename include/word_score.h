#pragma once

#include <map>
#include <array>
#include <string>


class WordScore
{
public:
    enum class Score
    {
        Empty,
        Incorrect,
        Yellow,
        Green
    };

    WordScore();
    ~WordScore(){};

    void set_score(const int position, const Score letter_score);
    Score get_score(const int position) const;
    int get_num_score() const;

    bool operator==(const WordScore &other) const;
    bool operator<(const WordScore &other) const;

private:
    std::array<Score, 5> _word_score;
    int size;
};
