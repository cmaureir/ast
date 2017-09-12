#ifndef POSTFIXEVALUATION_HPP
#define POSTFIXEVALUATION_HPP
#include "ShuntingYard.hpp"

class PostfixEvaluation
{
    public:
        PostfixEvaluation(std::stack<std::string> &q);
        ~PostfixEvaluation();

        std::stack<std::string> *input;

        float calculate();

};
#endif
