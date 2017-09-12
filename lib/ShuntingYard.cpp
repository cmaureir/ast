#include "ShuntingYard.hpp"

ShuntingYard::ShuntingYard(std::string line)
{
    this->line = line;
}

ShuntingYard::~ShuntingYard()
{

}

std::queue<std::string> ShuntingYard::parsing()
{
    std::istringstream input(line);

    while (input >> cc)
    {
        std::string c(1, cc);

        // Checking if the current element is a number
        if (p.check_number(c))
        {
            output.push(c);
        }

        // Checking operators
        else if (p.check_operator(c))
        {
            // Verifying precedence
            while (!p.operators.empty() && p.check_precedence(p.operators.top(), c))
            {
                output.push(p.operators.top());
                p.operators.pop();
            }
            p.operators.push(c);
        }

        // Checking left-bracket
        else if (p.check_left_bracket(c))
        {
            p.operators.push(c);
        }

        // Checking right-bracket
        else if (p.check_right_bracket(c))
        {
            while (!p.operators.empty() && !p.check_left_bracket(p.operators.top()))
            {
                output.push(p.operators.top());
                p.operators.pop();
            }

            // Verify missing left brackets
            if (!p.check_left_bracket(p.operators.top()))
            {
                throw std::invalid_argument("Mismatched parentheses: No left bracket");
            }

            p.operators.pop();
        }
    }

    while (!p.operators.empty())
    {
        // Remaining elements cannot be parentheses
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
