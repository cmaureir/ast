#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <iterator>
#include <algorithm>
#include <stack>

class Parser
{
    public:
        Parser();
        ~Parser();

        std::queue<float> numbers;
        std::stack<std::string> operators;

        std::vector<std::string> valid_operators = {"+", "-", "/", "*"};
        std::vector<std::string> left_brackets = {"{", "(", "["};
        std::vector<std::string> right_brackets = {"}", ")", "]"};

        bool check_number(std::string s);
        bool check_operator(std::string s);
        bool check_left_bracket(std::string s);
        bool check_right_bracket(std::string s);
        bool check_precedence(std::string a, std::string b);
};
