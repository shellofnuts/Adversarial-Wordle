#include "file_reader.h"

#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <memory>

const std::string WHITESPACE = " \n\r\t\f\v\"";

std::string ltrim(const std::string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string &s)
{
    return rtrim(ltrim(s));
}

WordList::WordList(std::string filename)
{

    std::cout << "WordList Constructed\n";
    std::ifstream word_file(filename);
    std::string word_line;
    if (word_file.is_open())
    {
        while (std::getline(word_file, word_line))
        {
            this->add_word(trim(word_line));
        }
    }
    else
    {
        std::string error_msg = "Cannot locate file " + filename + " in .exe directory.";
        std::cout << error_msg << "\n";
        throw std::runtime_error(error_msg);
    }
}

bool WordList::check_word(std::string word) const
{
    if (word.size() > 5)
    {
        return false;
    }
    for (const char &letter : word)
    {
        if (letter > 'z' || letter < 'A')
        {
            return false;
        }
    }
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    return _word_checker.search(word);
}

bool WordList::add_word(const std::string &word)
{
    _available_word_list.emplace(word);
    _word_checker.insert(word);
    return true;
}

void WordList::print_set() const
{
    for (auto i : _available_word_list)
    {
        std::cout << i << "\n";
    }
}

const std::set<std::string> &WordList::get_word_list() const
{
    return _available_word_list;
}