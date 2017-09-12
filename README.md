Create a C++ program that can parse and evaluate arithmetic expressions.
Parsing and evaluating should be two independent steps that are separated by a data structure (the AST).

The program should not use anything apart from the C++11 STL.

Arithmetic expressions consist of decimal numbers combined using the binary
operators +, *, /, - and parentheses and should respect the usual precedence relations.

The program should detect invalid input and report an appropriate error.

Unit tests are appreciated.

Example:

On input `(4 + 5 * (7 - 3)) - 2`, the program should output `22`
