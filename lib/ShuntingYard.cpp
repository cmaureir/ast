#include "ShuntingYard.hpp"

ShuntingYard::ShuntingYard(std::string line)
{
    this->line = line;
}

ShuntingYard::~ShuntingYard()
{

}

std::stack<std::string> ShuntingYard::parsing()
{
    std::istringstream input(line);
    bool prev_number = false;

    while (input >> cc)
    {
        std::string c(1, cc);

        // Checking if the current element is a number
        if (p.check_number(c))
        {
            if (prev_number)
            {
                std::string num = output.top()+c;
                output.pop();
                output.push(num);
            }
            else
            {
                output.push(c);
                prev_number = true;
            }
        }

        // Checking operators
        else if (p.check_if_in(c, p.valid_operators))
        {
            prev_number = false;
            // Verifying precedence
            while (!p.operators.empty() && p.check_precedence(p.operators.top(), c))
            {
                output.push(p.operators.top());
                p.operators.pop();
            }
            p.operators.push(c);
        }

        // Checking left-bracket
        else if (p.check_if_in(c, p.left_brackets))
        {
            prev_number = false;
            p.operators.push(c);
        }

        // Checking right-bracket
        else if (p.check_if_in(c, p.right_brackets))
        {
            prev_number = false;
            while (!p.operators.empty() && !p.check_if_in(p.operators.top(), p.left_brackets))
            {
                output.push(p.operators.top());
                p.operators.pop();
            }

            // Verify missing left brackets
            if (!p.check_if_in(p.operators.top(), p.left_brackets))
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
        if (p.check_if_in(t, p.left_brackets) || p.check_if_in(t, p.right_brackets))
        {
            throw std::invalid_argument("Mismatched parentheses: Extra bracket");
        }

        output.push(p.operators.top());
        p.operators.pop();
    }

    // reversing stack
    std::stack<std::string> oo;
    while(!output.empty())
    {
        oo.push(output.top());
        output.pop();
    }
    output = oo;

    return output;
}

void ShuntingYard::print_result()
{
    while (!output.empty())
    {
        std::cout << output.top() << " ";
        output.pop();
    }
    std::cout << std::endl;
}
