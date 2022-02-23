#include "display.h"

#include <cctype>

void print_incorrect(char letter)
{
    std::cout << "\033[38;5;252m"<< (char)toupper(letter) << "\033[0m";
    std::cout << "\t";
}

void print_yellow(char letter)
{
    std::cout << "\033[38;5;220m"<< (char)toupper(letter) << "\033[0m";
    std::cout << "\t";
}

void print_green(char letter)
{
    std::cout << "\033[38;5;40m"<< (char)toupper(letter) << "\033[0m";
    std::cout << "\t";
}

void print_empty(char letter)
{
    std::cout << "\033[38;5;196" << (char)toupper(letter) << "\033[0m";
    std::cout << "\t";
}

Display::Display()
{

}

void Display::update_display() const
{
    for (auto i = 0; i < _guesses.size(); ++i)
    {
        const auto &word = _guesses[i];
        const auto &score = _game_state[i];

        for (auto j = 0; j < 5; ++j)
        {
            switch (score.get_score(j))
            {
            case WordScore::Score::Yellow:
                print_yellow(word[j]);
                break;

            case WordScore::Score::Green:
                print_green(word[j]);
                break;
            
            case WordScore::Score::Incorrect:
                print_incorrect(word[j]);
                break;
            
            default:
                print_empty(word[j]);
                break;
            }
        }
        std::cout << "\n";
    }
}

void Display::add_guess(const std::string user_guess, const WordScore score)
{
    _guesses.emplace_back(user_guess);
    _game_state.emplace_back(score);
}