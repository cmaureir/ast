#include "lib/Parser.hpp"
#include "lib/ShuntingYard.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    string line;
    queue<string> output;

    getline(cin, line);

    ShuntingYard sy(line);
    try
    {
        output = sy.run();
    }
    catch (const std::invalid_argument &e)
    {
        return 0;
    }


    sy.print_result();

    return 0;
}
