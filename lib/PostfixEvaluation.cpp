#include "PostfixEvaluation.hpp"

PostfixEvaluation::PostfixEvaluation(std::stack<std::string> &q)
{
    this->input = &q;
}

PostfixEvaluation::~PostfixEvaluation(){}

float PostfixEvaluation::calculate()
{
    int op1 = 0;
    int op2 = 0;
    float result = 0;
    std::stack<std::string> result_stack;

    while (!input->empty())
    {
        std::string s = input->top();
        input->pop();

        if  (s == "+" || s == "-" || s == "*" || s == "/")
        {
            op1 = std::stoi(result_stack.top());
            result_stack.pop();
            op2 = std::stoi(result_stack.top());
            result_stack.pop();

            if (s == "+")      result = op2 + op1;
            else if (s == "-") result = op2 - op1;
            else if (s == "*") result = op2 * op1;
            else if (s == "/") result = op2 / op1;

            result_stack.push(std::to_string(result));
        }
        else
        {
            result_stack.push(s);
        }
    }
    return std::stof(result_stack.top());
}
