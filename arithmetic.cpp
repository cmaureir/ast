#include "lib/Parser.hpp"
#include "lib/ShuntingYard.hpp"
#include "lib/PostfixEvaluation.hpp"

int main(int argc, char *argv[])
{
    std::string line; // Input line
    std::stack<std::string> output;  // Output for the ShuntingYard algorithm

    getline(std::cin, line);  // Reading line and initialising ShuntingYard


    // Parsing process
    ShuntingYard sy(line);

    try
    {
        sy.parsing();
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 0;
    }

    // Print output from ShuntingYard in RPN
    sy.print_result();

    // Evaluation process
    PostfixEvaluation pe;
    try
    {
        // RPN Evaluation
        std::cout << pe.rpn_evaluation(sy.get_rpn()) <<std::endl;

        // AST Evaluation
        std::cout << pe.ast_evaluation(sy.get_ast()) << std::endl;
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 0;
    }

    return 0;
}

