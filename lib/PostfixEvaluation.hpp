#ifndef POSTFIXEVALUATION_HPP
#define POSTFIXEVALUATION_HPP
#include "ShuntingYard.hpp"

class PostfixEvaluation
{
    public:
        PostfixEvaluation();
        ~PostfixEvaluation();

        float rpn_evaluation(std::stack<std::string> input);
        float ast_evaluation(Node* ast);

    private:
        bool is_number(const std::string &s);
};
#endif
