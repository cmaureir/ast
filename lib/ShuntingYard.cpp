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
    std::stack<Node*> ast_stack;
    std::string op;

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

                std::cout << "> Push: " << num << std::endl;
                ast_stack.push(new Node(num));
            }
            else
            {
                output.push(c);
                std::cout << "> Push: " << c << std::endl;
                ast_stack.push(new Node(c));
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
                op = p.operators.top();
                output.push(op);
                p.operators.pop();

                Node *op2 = ast_stack.top();
                ast_stack.pop();
                Node *op1 = ast_stack.top();
                ast_stack.pop();

                std::cout << "> 1Push: " << op << " " << op1->value << " " << op2->value << std::endl;
                ast_stack.push(new Node(op, op1, op2));

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
                op = p.operators.top();
                output.push(op);
                p.operators.pop();

                Node *op2 = ast_stack.top();
                ast_stack.pop();
                Node *op1 = ast_stack.top();
                ast_stack.pop();


                std::cout << "> 2Push: " << op << " " << op1->value << " " << op2->value << std::endl;
                ast_stack.push(new Node(op, op1, op2));
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

        op = p.operators.top();
        output.push(op);
        p.operators.pop();


        Node *op2 = ast_stack.top();
        ast_stack.pop();
        Node *op1 = ast_stack.top();
        ast_stack.pop();

        std::cout << "> 3Push: " << op << " " << op1->value << " " << op2->value << std::endl;
        ast_stack.push(new Node(op, op1, op2));

    }

    std::cout << "AST size: " << ast_stack.size() << std::endl;
    Node *tmp = ast_stack.top();
    while(tmp->left != nullptr)
    {
        std::cout << "AST value: " << tmp->value << std::endl;
        std::cout << "AST l: "     << tmp->left->value << std::endl;
        std::cout << "AST r: "     << tmp->right->value << std::endl;
        //std::cout << "AST r: "     << tmp.right->right->value << std::endl;
        //std::cout << "AST value: " << tmp.value << std::endl;
        tmp = tmp->left;
        getchar();
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
