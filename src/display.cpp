#include "display.h"

#include <cctype>
#include <array>

std::string SPACE = "    ";

void print_incorrect(char letter)
{
    std::cout << "\033[38;5;246m" << (char)toupper(letter) << "\033[0m";
    std::cout << SPACE;
}

void print_yellow(char letter)
{
    std::cout << "\033[38;5;220m" << (char)toupper(letter) << "\033[0m";
    std::cout << SPACE;
}

void print_green(char letter)
{
    std::cout << "\033[38;5;40m" << (char)toupper(letter) << "\033[0m";
    std::cout << SPACE;
}

void print_empty(char letter)
{
    std::cout << "\033[38;5;15m" << (char)toupper(letter) << "\033[0m";
    std::cout << SPACE;
}

void Display::print_keyboard() const
{
    for (const auto &i : _keyboard)
    {
        format_word(i);
        if (i == 'p')
        {
            std::cout << "\n   ";
        }
        else if (i == 'l')
        {
            std::cout << "\n      ";
        }
    }
    std::cout << "\n" << std::endl;
}

Display::Display()
{
    for (const auto &l : _keyboard)
    {
        _game_state[l] = WordScore::Score::Empty;
    }
    this->refresh_display();
}

void Display::refresh_display() const
{
    std::cout << "\033[0m\033[2J" << (SPACE + SPACE) << "\033[38;5;10mAdversarial Wordle\033[0m\n";
    std::cout << "Type \"help\" for rules on how to play!\n\n";
    for (auto i = 0; i < _guesses.size(); ++i)
    {
        std::cout << "> ";
        this->format_word(_guesses[i], _guesses_score[i]);
        std::cout << "\n";
    }
    std::cout << std::endl;
    print_keyboard();
}

void Display::format_word(const std::string &word, const WordScore &score) const
{
    for (auto j = 0; j < word.size(); j++)
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

void Display::format_word(const char &letter) const
{
    auto ptr = _game_state.find(letter);
    switch (ptr->second)
    {
    case WordScore::Score::Yellow:
        print_yellow(letter);
        break;

    case WordScore::Score::Green:
        print_green(letter);
        break;

    case WordScore::Score::Incorrect:
        print_incorrect(letter);
        break;

    default:
        print_empty(letter);
        break;
    }
}

void Display::update_display() const
{
    this->refresh_display();
}

void Display::update_display(std::string err_msg) const
{
    this->refresh_display();
    std::cout << err_msg << "\n";
}

void Display::add_guess(const std::string user_guess, const WordScore score)
{
    _guesses.emplace_back(user_guess);
    for (int i = 0; i < user_guess.size(); ++i)
    {
        _game_state[user_guess[i]] = score.get_score(i);
    }
    _guesses_score.emplace_back(score);
}

std::string Display::get_user_input()
{
    std::cout << "Guess: > \033[38;5;45m";
    std::string user_input;
    std::getline(std::cin, user_input);
    std::cout << "\033[0m";
    return user_input;
}