#include <iostream>
#include <sstream>
#include "lib/Parser.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    string line;
    char cc;

    Parser p;
    queue<string> output;

    getline(cin, line);
    istringstream ss(line);

    while (ss >> cc)
    {
        string c(1,cc);

        // Numbers
        if (p.check_number(c))
        {
            cout << "Pushing " << c  << " to the output queue" << endl;
            output.push(c);
        }

        else if (p.check_operator(c))
        {
            while (!p.operators.empty() && p.check_precedence(p.operators.top(), c))
            {
                cout << "Pushing " << p.operators.top()  << " to the operator stack" << endl;
                output.push(p.operators.top());
                p.operators.pop();
            }
            cout << "Pushing " << c  << " to the operator stack" << endl;
            p.operators.push(c);
        }

        else if (p.check_left_bracket(c))
        {
            cout << "Pushing " << c  << " to the operator stack" << endl;
            p.operators.push(c);
        }

        else if (p.check_right_bracket(c))
        {
            std::cout << "is a right bracket" << std::endl;
            while (!p.operators.empty() && !p.check_left_bracket(p.operators.top()))
            {
                cout << "Pushing " << p.operators.top()  << " to the output queue" << endl;
                output.push(p.operators.top());
                p.operators.pop();
            }
            /* if the stack runs out without finding a left bracket, then there are
            mismatched parentheses. */
            if (!p.check_left_bracket(p.operators.top()))
            {
                std::cerr << "[Error] Mismarched parentheses: No left-bracket" << std::endl;
                return 0;
            }
            p.operators.pop();
        }
    }

    while (!p.operators.empty())
    {
        /* if the operator token on the top of the stack is a bracket, then
        there are mismatched parentheses. */
        output.push(p.operators.top());
        p.operators.pop();
    }


    int i = 0;
    while (!output.empty())
    {
        string o = output.front();
        std::cout << o << " ";
        output.pop();
        i++;
    }
    std::cout << std::endl;

//if there are no more tokens to read:
//    while there are still operator tokens on the stack:
//        /* if the operator token on the top of the stack is a bracket, then
//        there are mismatched parentheses. */
//        pop the operator onto the output queue.

    return 0;
}
