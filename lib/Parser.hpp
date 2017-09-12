#ifndef PARSER_HPP
#define PARSER_HPP
#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <iterator>
#include <algorithm>
#include <stack>

class Parser
{
    public:
        Parser();
        ~Parser();

        // Stack for operators
        std::stack<std::string> operators;

        const std::vector<std::string> valid_operators = {"+", "-", "/", "*"};
        const std::vector<std::string> left_brackets = {"{", "(", "["};
        const std::vector<std::string> right_brackets = {"}", ")", "]"};

        bool check_number(std::string s);
        bool check_operator(std::string s);
        bool check_left_bracket(std::string s);
        bool check_right_bracket(std::string s);
        bool check_precedence(std::string a, std::string b);
};

#endif
