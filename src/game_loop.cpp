#include "game_loop.h"

Game::Game(std::string filename)
{
    // Populate major classes
    _internal_word_list = std::make_unique<WordList>(filename);
    _internal_display = std::make_unique<Display>();
    _internal_opponent = std::make_unique<Opponent>(*_internal_word_list);
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

std::string Game::get_input()
{
    std::string user_input = _internal_display->get_user_input();
    while (!_internal_word_list->check_word(user_input))
    {
        std::string err_msg = "\033[38;5;196m" + user_input + "\033[0m is an invalid word.\n";
        _internal_display->update_display(err_msg);
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