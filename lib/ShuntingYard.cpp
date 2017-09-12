#include "ShuntingYard.hpp"

ShuntingYard::ShuntingYard(std::string line)
{
    this->line = line;
}

ShuntingYard::~ShuntingYard()
{

}

std::queue<std::string> ShuntingYard::run()
{

    std::istringstream input(line);

    while (input >> cc)
    {
        std::string c(1, cc);

        if (p.check_number(c))
        {
            std::cout << "Pushing " << c  << " to the output queue" << std::endl;
            output.push(c);
        }

        else if (p.check_operator(c))
        {
            while (!p.operators.empty() && p.check_precedence(p.operators.top(), c))
            {
                std::cout << "Pushing " << p.operators.top()  << " to the operator stack" << std::endl;
                output.push(p.operators.top());
                p.operators.pop();
            }
            std::cout << "Pushing " << c  << " to the operator stack" << std::endl;
            p.operators.push(c);
        }

        else if (p.check_left_bracket(c))
        {
            std::cout << "Pushing " << c  << " to the operator stack" << std::endl;
            p.operators.push(c);
        }

        else if (p.check_right_bracket(c))
        {
            std::cout << "is a right bracket" << std::endl;
            while (!p.operators.empty() && !p.check_left_bracket(p.operators.top()))
            {
                std::cout << "Pushing " << p.operators.top()  << " to the output queue" << std::endl;
                output.push(p.operators.top());
                p.operators.pop();
            }
            if (!p.check_left_bracket(p.operators.top()))
            {
                throw std::invalid_argument("Mismatched parentheses: No left bracket");

            }
            p.operators.pop();
        }
    }

    while (!p.operators.empty())
    {
        std::string t = p.operators.top();
        if (p.check_left_bracket(t) || p.check_right_bracket(t))
        {
            throw std::invalid_argument("Mismatched parentheses: Extra bracket");
        }
        output.push(p.operators.top());
        p.operators.pop();
    }

    return output;
}

void ShuntingYard::print_result()
{
    int i = 0;
    while (!output.empty())
    {
        std::string o = output.front();
        std::cout << o << " ";
        output.pop();
        i++;
    }
    std::cout << std::endl;
}
