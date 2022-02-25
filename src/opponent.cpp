#include <opponent.h>

#include <ctime>
#include <cstdlib>
#include <algorithm>

Opponent::Opponent(const WordList &master_record)
{
    for (const std::string &i : master_record.get_word_list())
    {
        _word_set.emplace_back(&i);
    }
}

const WordScore Opponent::prune_words(const std::string user_guess)
{
    std::map<WordScore, std::vector<const std::string *>> scoring_sheet;
    for (auto &word : _word_set)
    {
        WordScore current_score;
        for (size_t user_i = 0; user_i < user_guess.size(); ++user_i)
        {
            if (current_score.get_score(user_i) != WordScore::Score::Empty)
            {
                continue;
            }
            size_t w_count = std::count(word->begin(), word->end(), user_guess[user_i]);
            if (w_count == 0)
            {
                current_score.set_score(user_i, WordScore::Score::Incorrect);
                continue;
            }

            // Dealing with duplicates.
            std::vector<size_t> pos_vec = {user_i};
            while (pos_vec.back() != std::string::npos)
            {
                if (user_guess[pos_vec.back()] == (*word)[pos_vec.back()])
                {
                    current_score.set_score(pos_vec.back(), WordScore::Score::Green);
                    if (pos_vec.size() > w_count)
                    {
                        // Get first excess yellow and remove it.
                        for (auto &pos : pos_vec)
                        {
                            if (current_score.get_score(pos) == WordScore::Score::Yellow)
                            {
                                current_score.set_score(pos, WordScore::Score::Incorrect);
                                break;
                            }
                        }
                    }
                }
                // Only count the first yellows till max, not subsequent
                else if (pos_vec.size() > w_count)
                {
                    current_score.set_score(pos_vec.back(), WordScore::Score::Incorrect);
                }
                else
                {
                    current_score.set_score(pos_vec.back(), WordScore::Score::Yellow);
                }
                pos_vec.emplace_back(user_guess.find(user_guess[user_i], pos_vec.back() + 1));
            }
        }
        scoring_sheet[current_score].emplace_back(word);
    }

    auto ptr = std::max_element(scoring_sheet.begin(), scoring_sheet.end(),
                                [](const std::pair<WordScore, std::vector<const std::string *>> &p1, const std::pair<WordScore, std::vector<const std::string *>> &p2)
                                {
                                    return p1.second.size() < p2.second.size();
                                });

    _word_set = std::move(ptr->second);
    _previous_score = ptr->first;
    return _previous_score;
}

void Opponent::print_word_set() const
{
    for (const auto &i : _word_set)
    {
        std::cout << *i << "\n";
    }
}

int Opponent::get_previous_num_score() const
{
    return _previous_score.get_num_score();
}

std::string Opponent::get_random_word() const
{
    srand(time(0));
    std::string word = *(_word_set[rand() % _word_set.size()]);
    return word;
}