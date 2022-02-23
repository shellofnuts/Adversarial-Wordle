#include <opponent.h>

#include <algorithm>

Opponent::Opponent(const WordList &master_record)
{
    _word_set = master_record.get_word_list();
}

const WordScore Opponent::prune_words(const std::string user_guess)
{
    std::map<WordScore, std::vector<std::string>> scoring_sheet;
    for (auto &word : _word_set)
    {
        WordScore current_score;
        for (int user_i = 0; user_i < user_guess.size(); ++user_i)
        {
            //TODO: Need to check for duplicates and mark scores in proper order
            //      If an E appears twice in guess but once in word, only score first (unless 2nd is green).
            int l_count = std::count(word.begin(), word.end(), user_guess[user_i]);
            if (l_count == 0)
            {
                current_score.set_score(user_i, WordScore::Score::Incorrect);
            }
            else if (l_count == 1)
            {
                if (user_guess[user_i] == word[user_i])
                {
                    current_score.set_score(user_i, WordScore::Score::Green);
                }
                else
                {
                    current_score.set_score(user_i, WordScore::Score::Yellow);
                }
            }
            else
            {
                //TODO: Need to properly check for duplicates.
                if (user_guess[user_i] == word[user_i])
                {
                    current_score.set_score(user_i, WordScore::Score::Green);
                }
                else
                {
                    current_score.set_score(user_i, WordScore::Score::Yellow);
                }
            }
        }
        scoring_sheet[current_score].emplace_back(word);
    }

    auto ptr = std::max_element(scoring_sheet.begin(), scoring_sheet.end(),
                                [](const std::pair<WordScore, std::vector<std::string>> &p1, const std::pair<WordScore, std::vector<std::string>> &p2){
                                    return p1.second.size() < p2.second.size();
                                }
                                );
    
    std::set<std::string> new_set(ptr->second.begin(), ptr->second.end());
    _word_set = new_set;
    return ptr->first;
}


void Opponent::print_word_set() const
{
    for (const auto &i: _word_set)
    {
        std::cout << i << "\n";
    }
}