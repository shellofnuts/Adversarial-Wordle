#include "game_loop.h"

int main()
{
    // Program injection point.
    Game game_instance("allowed.txt", "answers.txt");
    game_instance.play();
}