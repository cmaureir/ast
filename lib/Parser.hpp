#ifndef PARSER_HPP
#define PARSER_HPP
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <stack>
#include <regex>

class Node
{
    public:
        Node() {

        }
        Node(const std::string value) : value(value)
        {
        }
        Node(const std::string value, Node* left, Node* right)
            : value(value)
            , left(left)
            , right(right)
        {
        }
        Node& operator=(const Node &b)
        {
            value = b.value;
            left  = b.left;
            right = b.right;
        }

    std::string value = "";
    Node *left = nullptr;
    Node *right = nullptr;
};


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
        bool check_if_in(std::string s, const std::vector<std::string> v);
        bool check_precedence(std::string a, std::string b);
};

#endif
