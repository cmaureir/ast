#include "Parser.hpp"

// Empty constructor and destructor
Parser::Parser() {}
Parser::~Parser() {}

bool Parser::check_number(std::string s)
{
    try
    {
        float n = std::stof(s);
    }
    catch(std::invalid_argument &ia)
    {
        return false;
    }

    return true;
}

bool Parser::check_operator(std::string s)
{

    auto r = std::find(std::begin(valid_operators), std::end(valid_operators), s);

    if (r != std::end(valid_operators))
    {
        return true;
    }

    return false;
}

bool Parser::check_left_bracket(std::string s)
{

    auto r = std::find(std::begin(left_brackets), std::end(left_brackets), s);

    if (r != std::end(left_brackets))
    {
        return true;
    }

    return false;
}

bool Parser::check_right_bracket(std::string s)
{

    auto r = std::find(std::begin(right_brackets), std::end(right_brackets), s);

    if (r != std::end(right_brackets))
    {
        return true;
    }

    return false;
}

// Check if `a` precedes `b`
bool Parser::check_precedence(std::string a, std::string b)
{
    if (a == "/" || a == "*")
    {
        return true;
    }
    return false;
}

