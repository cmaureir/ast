#include "lib/Parser.hpp"
#include "lib/ShuntingYard.hpp"
#include "lib/PostfixEvaluation.hpp"

int main(int argc, char *argv[])
{
    // Input line
    std::string line;

    // Output for the ShuntingYard algorithm
    std::stack<std::string> output;
    // Reading line and initialising ShuntingYard
    getline(std::cin, line);
    ShuntingYard sy(line);

    try
    {
        output = sy.parsing();
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 0;
    }

    // Print output from ShuntingYard
    sy.print_result();

    PostfixEvaluation pe(output);
    std::cout << pe.calculate() <<std::endl;

    return 0;
}
