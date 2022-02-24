#include "game_loop.h"

int main()
{
    // Program injection point.
    Game game_instance("wordle_words.txt");
    game_instance.play();
}