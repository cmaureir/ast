#include "ShuntingYard.hpp"

ShuntingYard::ShuntingYard(std::string line )
{
    this->line = line;
}

ShuntingYard::~ShuntingYard()
{

}

Node* ShuntingYard::get_ast()
{
    return this->ast_stack.top();
}

std::stack<std::string> ShuntingYard::get_rpn()
{
    return this->rpn;
}

std::string ShuntingYard::clear_line(const std::string s)
{
    // Small regex modification to the line
    std::string tmp, ff;


    // Remove double `-` for one `+`
    tmp = std::regex_replace(s, std::regex("\\-\\-"), "+");

    // Remove multiple `+` to just one
    tmp = std::regex_replace(tmp, std::regex("\\+\\++"), "+");

    // Remove multiple `-+` to '-`
    tmp = std::regex_replace(tmp, std::regex("\\-\\+"), "-");

    // Remove multiple `+-` to '-`
    tmp = std::regex_replace(tmp, std::regex("\\+\\-"), "-");

    // We will remove plus symbols after `*`
    tmp = std::regex_replace(tmp, std::regex("\\*\\+"), "*");

    // We will remove plus symbols after `/`
    tmp = std::regex_replace(tmp, std::regex("\\/\\+"), "/");

    // Removing whitespaces
    tmp = std::regex_replace(tmp, std::regex("\\ "), "");

    // We will enclose all the negative numbers in parenthesis,
    // to handle negative numbers properly
    std::regex_replace(std::back_inserter(ff), tmp.begin(), tmp.end(),
        std::regex("-\\s?(\\d+\\.?\\d*)"), "+\(-$1)");

    // We will remove plus symbols at the beginning of the line
    ff = std::regex_replace(ff, std::regex("^\\+"), "");


    // Check for invalid tokens
    if(ff.find_first_not_of("0123456789(){}[]-+/*.") != std::string::npos)
        throw std::invalid_argument("Invalid token: An invalid token was entered");

    return ff;
}

void ShuntingYard::parsing()
{
    std::istringstream input(clear_line(line));
    bool prev_number = false;
    bool float_number = false;
    bool prev_par = false;
    bool prev_minus = false;
    std::string op;

    while (input >> cc)
    {
        std::string c(1, cc);

        // Checking if the current element is a number
        if (p.check_number(c))
        {
            // Handling numbers with more than one digit
            if (prev_number)
            {
                std::string num = "";
                if (!rpn.empty())
                {
                    num = rpn.top();
                }

                if (p.check_number(num))
                {
                    if (float_number)
                    {
                        num = num+".";
                        float_number = false;
                    }
                    num = num+c;
                }
                //else if (float_number)
                //{
                //    num = "0."+c;
                //    float_number = false;
                //}

                if (!rpn.empty())
                {
                    rpn.pop();
                }
                rpn.push(num);

                if (!ast_stack.empty())
                {
                    ast_stack.pop();
                }
                ast_stack.push(new Node(num));
            }
            else
            {
                if (prev_minus)
                {
                    // Using internal symbol `m` to represent negative numbers
                    c = "m"+c;
                    prev_minus = false;
                }

                rpn.push(c);
                ast_stack.push(new Node(c));
                prev_number = true;
            }
            prev_par = false;
            prev_number = true;
        }

        // Checking operators
        else if (p.check_if_in(c, p.valid_operators))
        {
            prev_number = false;
            float_number = false;
            // Checking for negative numbers
            if (prev_par && c == "-")
            {
                prev_minus = true;
                continue;
            }
            else if (prev_par && c == "+")
            {
                continue;
            }
            prev_par = false;

            // Verifying precedence
            while (!p.operators.empty() &&
                p.check_precedence(p.operators.top(), c))
            {
                op = p.operators.top();
                rpn.push(op);
                p.operators.pop();

                Node *op2 = ast_stack.top();
                ast_stack.pop();
                Node *op1 = ast_stack.top();
                ast_stack.pop();

                ast_stack.push(new Node(op, op1, op2));

            }
            p.operators.push(c);
        }

        // Checking left-bracket
        else if (p.check_if_in(c, p.left_brackets))
        {
            prev_number = false;
            float_number = false;
            prev_par = true;
            p.operators.push(c);
        }

        // Checking right-bracket
        else if (p.check_if_in(c, p.right_brackets))
        {
            prev_number = false;
            float_number = false;
            while (!p.operators.empty() &&
                !p.check_if_in(p.operators.top(), p.left_brackets))
            {
                op = p.operators.top();
                rpn.push(op);
                p.operators.pop();

                Node *op2 = ast_stack.top();
                ast_stack.pop();
                Node *op1 = ast_stack.top();
                ast_stack.pop();

                ast_stack.push(new Node(op, op1, op2));
            }

            // Verify missing left brackets
            if (p.operators.empty())
            {
                throw std::invalid_argument("Mismatched parentheses: Missing left bracket");
            }

            p.operators.pop();
        }
        else if (c == ".")
        {
            prev_number = true;
            float_number = true;
        }
    }

    while (!p.operators.empty())
    {
        // Remaining elements cannot be parentheses
        std::string t = p.operators.top();
        if (p.check_if_in(t, p.left_brackets) ||
            p.check_if_in(t, p.right_brackets))
        {
            throw std::invalid_argument("Mismatched parentheses: Extra bracket");
        }

        op = p.operators.top();
        rpn.push(op);
        p.operators.pop();

        Node *op2 = ast_stack.top();
        ast_stack.pop();
        Node *op1 = ast_stack.top();
        ast_stack.pop();

        ast_stack.push(new Node(op, op1, op2));
    }

    // reversing stack
    std::stack<std::string> oo;
    while(!rpn.empty())
    {
        oo.push(rpn.top());
        rpn.pop();
    }
    rpn = oo;
}

void ShuntingYard::print_result()
{
    std::stack<std::string> tmp = rpn;

    while (!tmp.empty())
    {
        std::cout << tmp.top() << " ";
        tmp.pop();
    }
    std::cout << std::endl;
}
