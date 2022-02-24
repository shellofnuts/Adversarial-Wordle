#include <word_score.h>

#include <exception>
#include <math.h>

WordScore::WordScore()
{
    for (int i = 0; i < _word_score.size(); ++i)
    {
        _word_score[i] = WordScore::Score::Empty;
    }
}

WordScore::Score WordScore::get_score(const int i) const
{
    if (i < 0 || i >= 5)
    {
        throw std::exception();
    }
    return _word_score[i];
}

void WordScore::set_score(const int i, const WordScore::Score score)
{
    if (i < 0 || i >= 5)
    {
        throw std::exception();
    }
    _word_score[i] = score;
}

bool WordScore::operator==(const WordScore &other) const
{
    for (int i = 0; i < 5; ++i)
    {
        if (this->get_score(i) != other.get_score(i))
        {
            return false;
        }
    }
    return true;
}

bool WordScore::operator<(const WordScore &other) const
{
    return this->get_num_score() < other.get_num_score();
}

int WordScore::get_num_score() const
{
    int total_score = 0;
    for (int i = 0; i < 5; ++i)
    {
        WordScore::Score curr_score = this->get_score(i);
        switch (curr_score)
        {
        case WordScore::Score::Yellow:
            total_score += 1 * pow(10, i);
            break;
        
        case WordScore::Score::Green:
            total_score += 2 * pow(10, i);
            break;
        default:
            total_score += 0;
            break;
        }
    }
    return total_score;
}

