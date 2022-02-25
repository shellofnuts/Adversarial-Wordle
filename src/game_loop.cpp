#include "game_loop.h"

#include <fstream>

Game::Game(std::string allowed_words, std::string answers)
{
    // Populate major classes
    _internal_word_list = std::make_unique<WordList>(allowed_words);
    _internal_answers = std::make_unique<WordList>(answers);
    _internal_display = std::make_unique<Display>();
    _internal_opponent = std::make_unique<Opponent>(*_internal_answers);
}

void Game::play()
{
    while (!this->end_condition())
    {
        std::string user_input = get_input();
        update_opponent(user_input);
        update_board(user_input);
#ifdef _DEBUG
        _internal_opponent->print_word_set();
#endif
        current_iteration += 1;
    }
    if (_internal_opponent->get_previous_num_score() == 22222)
    {
        std::cout << "\033[38;5;10mSuccess!\033[0m" << std::endl;
    }
    else
    {
        std::cout<< "The hidden word was: " << _internal_opponent->get_random_word() << std::endl;
    }
}

bool Game::end_condition() const
{
    if (current_iteration >= MAX_GAME_ITERATIONS)
    {
        return true;
    }
    else if (_internal_opponent->get_previous_num_score() == 22222)
    {
        return true;
    }
    return false;
}

void help_info()
{
    std::ifstream help_file("help_info.txt");
    std::string line;
    if (help_file.is_open())
    {
        std::cout << "\033[2J";
        std::string ansi_escape = "\\033";
        while (std::getline(help_file, line))
        {
            std::string::size_type pos = 0;
            while ((pos = line.find(ansi_escape, pos)) != std::string::npos)
            {
                line.replace(pos, 4, "\033");
                pos += ansi_escape.size();
            }
            std::cout << line << "\n";
        }
    }
    std::cout << "\nPress any key to return: >";
    std::string tmp;
    std::getline(std::cin, tmp);
}

std::string Game::get_input()
{
    std::string user_input = _internal_display->get_user_input();
    while (!_internal_word_list->check_word(user_input))
    {
        if (user_input == "help")
        {
            help_info();
            _internal_display->update_display();
        }
        else
        {
            std::string err_msg = "\033[38;5;196m" + user_input + "\033[0m is an invalid word.\n";
            _internal_display->update_display(err_msg);
        }
        user_input = _internal_display->get_user_input();
    }
    return user_input;
}

void Game::update_opponent(const std::string &user_input)
{
    _internal_opponent->prune_words(user_input);
}

void Game::update_board(const std::string &user_input)
{
    _internal_display->add_guess(user_input, _internal_opponent->get_previous_score());
    _internal_display->update_display();
}