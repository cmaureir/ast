#include "PostfixEvaluation.hpp"

PostfixEvaluation::PostfixEvaluation(){}
PostfixEvaluation::~PostfixEvaluation(){}

bool PostfixEvaluation::is_number(const std::string &s)
{
    // Replace `m` for a `-`
    std::string tmp = std::regex_replace(s, std::regex("m"), "-");

    // Check if string format is a number
    if (std::regex_match(tmp, std::regex("[-+]?\\d+\\.?\\d*")))
    {
        return true;
    }
    return false;
}

// Evaluation of the RPN string expression
float PostfixEvaluation::rpn_evaluation(std::stack<std::string> input)
{
    float op1 = 0;
    float op2 = 0;
    float result = 0;
    std::stack<std::string> result_stack;

    while (!input.empty())
    {
        std::string s = input.top();
        input.pop();

        if  (s == "+" || s == "-" || s == "*" || s == "/")
        {
            op1 = std::stof(result_stack.top());
            result_stack.pop();

            op2 = std::stof(result_stack.top());
            result_stack.pop();

            if (s == "+")      { result = op2 + op1; }
            else if (s == "-") { result = op2 - op1; }
            else if (s == "*") { result = op2 * op1; }
            else if (s == "/") { result = op2 / op1; }

            result_stack.push(std::to_string(result));
        }
        else
        {
            // Handling negative numbers
            if (s.substr(0,1) == "m")
            {
                s.replace(0, 1, "-");
            }

            result_stack.push(s);
        }
    }

    return std::stof(result_stack.top());
}

// Recursive evaluation of the stack AST
float PostfixEvaluation::ast_evaluation(Node* ast)
{
    // Check null
    if (ast == nullptr)
    {
        throw std::invalid_argument("Invalid AST: nullptr" );
    }

    // Evaluation
    std::string s = ast->value;

    if (is_number(s))
    {
        // Handling negative numbers
        if (s.substr(0,1) == "m")
        {
            s = "-"+s.substr(1, s.length());
        }
        return std::stof(s);
    }
    else
    {
        float op1 = ast_evaluation(ast->left);
        float op2 = ast_evaluation(ast->right);

        if (s == "+")      { return op1 + op2; }
        else if (s == "-") { return op1 - op2; }
        else if (s == "*") { return op1 * op2; }
        else if (s == "/") { return op1 / op2; }
    }
}
