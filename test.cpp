#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"
#include "lib/ShuntingYard.hpp"
#include "lib/PostfixEvaluation.hpp"

TEST_CASE("Testing Parse methods")
{
    Parser p;

    SECTION("check_number(std::string)")
    {
        REQUIRE( p.check_number(std::string("3")) == true );
        REQUIRE( p.check_number(std::string("1.3")) == true );
        REQUIRE( p.check_number(std::string("(")) == false );
        REQUIRE( p.check_number(std::string("+")) == false );
    }

    SECTION("Check operators")
    {
        REQUIRE( p.check_if_in(std::string("+"), p.valid_operators) == true );
        REQUIRE( p.check_if_in(std::string("-"), p.valid_operators) == true );
        REQUIRE( p.check_if_in(std::string("/"), p.valid_operators) == true );
        REQUIRE( p.check_if_in(std::string("*"), p.valid_operators) == true );
        REQUIRE( p.check_if_in(std::string("?"), p.valid_operators) == false );
    }

    SECTION("Check left brackets")
    {
        REQUIRE( p.check_if_in(std::string("("), p.left_brackets) == true );
        REQUIRE( p.check_if_in(std::string("["), p.left_brackets) == true );
        REQUIRE( p.check_if_in(std::string("{"), p.left_brackets) == true );
        REQUIRE( p.check_if_in(std::string("}"), p.left_brackets) == false );
    }

    SECTION("Check right brackets")
    {
        REQUIRE( p.check_if_in(std::string(")"), p.right_brackets) == true );
        REQUIRE( p.check_if_in(std::string("]"), p.right_brackets) == true );
        REQUIRE( p.check_if_in(std::string("}"), p.right_brackets) == true );
        REQUIRE( p.check_if_in(std::string("{"), p.right_brackets) == false );
    }

    SECTION("check_precedence(std::string a, std::string b)")
    {
        REQUIRE( p.check_precedence(std::string("+"), std::string("*")) == false );
        REQUIRE( p.check_precedence(std::string("*"), std::string("/")) == true );
        REQUIRE( p.check_precedence(std::string("/"), std::string("/")) == true );
        REQUIRE( p.check_precedence(std::string("-"), std::string("*")) == false );
    }
}

TEST_CASE("Testing Shunting Yard implementation")
{
    ShuntingYard sy1(std::string("4+3"));
    sy1.parsing();
    std::stack<std::string> out1 = sy1.get_rpn();
    std::stack<std::string> out2;
    out2.push("+");
    out2.push("3");
    out2.push("4");


    for (int i = 0; i < out1.size(); i++)
    {
        REQUIRE (out1.top() ==  out2.top() );
        out1.pop();
        out2.pop();
    }

    ShuntingYard sy2(std::string("3 + 4 * 2 / (1 - 5)"));
    sy2.parsing();
    std::stack<std::string> out3 = sy2.get_rpn();
    std::stack<std::string> out4;
    out4.push("+");
    out4.push("/");
    out4.push("-");
    out4.push("5");
    out4.push("1");
    out4.push("*");
    out4.push("2");
    out4.push("4");
    out4.push("3");

    for (int i = 0; i < out1.size(); i++)
    {
        REQUIRE (out3.top() ==  out4.top() );
        out3.pop();
        out4.pop();
    }

}

TEST_CASE("Testing PostfixEvaluation implementation")
{

    ShuntingYard sy01(std::string("((15/(7-(1+1)))*3)-(2+(1+1))")); // 5
    ShuntingYard sy02(std::string("5 * 3 + (4 + 2 / 2 * 8)")); // 27
    ShuntingYard sy03(std::string("1+2+3+4"));       // 10
    ShuntingYard sy04(std::string("1*2*3*4"));       // 24
    ShuntingYard sy05(std::string("1-2-3-4"));       // -8
    ShuntingYard sy06(std::string("1/2/3/4"));       // 0.0416667
    ShuntingYard sy07(std::string("1*2+3*4"));       // 14
    ShuntingYard sy08(std::string("1+2*3+4"));       // 11
    ShuntingYard sy09(std::string("(1+2)*(3+4)"));   // 21
    ShuntingYard sy10(std::string("1+(2*3)*(4+5)")); // 55
    ShuntingYard sy11(std::string("1+(2*3)/4+5"));   // 7.5
    ShuntingYard sy12(std::string("5/(4+3)/2"));     // 0.357143
    ShuntingYard sy13(std::string("1 + 2.5"));       // 3.5
    ShuntingYard sy14(std::string("125"));           // 125
    ShuntingYard sy15(std::string("-1"));            // -1
    ShuntingYard sy16(std::string("-1+(-2)"));       // -3
    ShuntingYard sy17(std::string("-1+(-2.0)"));     // -3
    ShuntingYard sy18(std::string("()+()+()+2"));    // 2
    ShuntingYard sy19(std::string("-1.0*3+0.1-1.")); // -3.9
    ShuntingYard sy20(std::string("-99.2+0.2-1"));   // 100

    sy01.parsing();
    sy02.parsing();
    sy03.parsing();
    sy04.parsing();
    sy05.parsing();
    sy06.parsing();
    sy07.parsing();
    sy08.parsing();
    sy09.parsing();
    sy10.parsing();
    sy11.parsing();
    sy12.parsing();
    sy13.parsing();
    sy14.parsing();
    sy15.parsing();
    sy16.parsing();
    sy17.parsing();
    sy18.parsing();
    sy19.parsing();
    sy20.parsing();

    PostfixEvaluation pe01;
    REQUIRE(pe01.ast_evaluation(sy01.get_ast()) == 5);
    REQUIRE(pe01.ast_evaluation(sy02.get_ast()) == 27);
    REQUIRE(pe01.ast_evaluation(sy03.get_ast()) == 10);
    REQUIRE(pe01.ast_evaluation(sy04.get_ast()) == 24);
    REQUIRE(pe01.ast_evaluation(sy05.get_ast()) == -8);
    REQUIRE(fabs(pe01.ast_evaluation(sy06.get_ast()) - 0.0416667) < 1e-5);
    REQUIRE(pe01.ast_evaluation(sy07.get_ast()) == 14);
    REQUIRE(pe01.ast_evaluation(sy08.get_ast()) == 11);
    REQUIRE(pe01.ast_evaluation(sy09.get_ast()) == 21);
    REQUIRE(pe01.ast_evaluation(sy10.get_ast()) == 55);
    REQUIRE(fabs(pe01.ast_evaluation(sy11.get_ast()) - 7.5) < 1e-5);
    REQUIRE(fabs(pe01.ast_evaluation(sy12.get_ast()) - 0.357143) < 1e-5);
    REQUIRE(fabs(pe01.ast_evaluation(sy13.get_ast()) - 3.5) < 1e-5);
    REQUIRE(pe01.ast_evaluation(sy14.get_ast()) == 125);
    REQUIRE(pe01.ast_evaluation(sy15.get_ast()) == -1);
    REQUIRE(pe01.ast_evaluation(sy16.get_ast()) == -3);
    REQUIRE(pe01.ast_evaluation(sy17.get_ast()) == -3);
    REQUIRE(pe01.ast_evaluation(sy18.get_ast()) == 2);
    REQUIRE(fabs(pe01.ast_evaluation(sy19.get_ast()) - (-3.9)) < 1e-5);
    REQUIRE(fabs(pe01.ast_evaluation(sy20.get_ast()) - (-100.0)) < 1e-5);

}
