#ifndef SHUNTINGYARD_HPP
#define SHUNTINGYARD_HPP
#include "Parser.hpp"

class ShuntingYard
{
    public:
        ShuntingYard(std::string line);
        ~ShuntingYard();

        char cc;
        std::string s;
        std::string line;
        Parser p;
        std::stack<std::string> output;

        std::stack<std::string> parsing();
        void print_result();
};
#endif
