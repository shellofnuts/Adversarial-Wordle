#include "file_reader.h"
#include "opponent.h"
#include "display.h"

int main()
{
    // Program injection point.
    WordList my_list("wordle_word.txt");

    Opponent my_opponent(my_list);
    Display my_display;
    my_display.add_guess("gourd", my_opponent.prune_words("gourd"));
    my_display.add_guess("class", my_opponent.prune_words("class"));
    my_display.add_guess("stove", my_opponent.prune_words("stove"));
    my_display.add_guess("mambo", my_opponent.prune_words("mambo"));
    my_display.add_guess("light", my_opponent.prune_words("light"));
    my_display.add_guess("reply", my_opponent.prune_words("reply"));  
    my_display.add_guess("quell", my_opponent.prune_words("quell"));  
    my_display.add_guess("dwell", my_opponent.prune_words("dwell"));  
    
    my_display.update_display();
    my_opponent.print_word_set();
}