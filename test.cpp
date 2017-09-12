#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"
#include "lib/ShuntingYard.hpp"

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

    SECTION("check_operator(std::string)")
    {
        REQUIRE( p.check_operator(std::string("+")) == true );
        REQUIRE( p.check_operator(std::string("-")) == true );
        REQUIRE( p.check_operator(std::string("/")) == true );
        REQUIRE( p.check_operator(std::string("*")) == true );
        REQUIRE( p.check_operator(std::string("?")) == false );
    }

    SECTION("check_left_bracket(std::string s)")
    {
        REQUIRE( p.check_left_bracket(std::string("(")) == true );
        REQUIRE( p.check_left_bracket(std::string("[")) == true );
        REQUIRE( p.check_left_bracket(std::string("{")) == true );
        REQUIRE( p.check_left_bracket(std::string("}")) == false );
    }

    SECTION("check_right_bracket(std::string s)")
    {
        REQUIRE( p.check_right_bracket(std::string(")")) == true );
        REQUIRE( p.check_right_bracket(std::string("]")) == true );
        REQUIRE( p.check_right_bracket(std::string("}")) == true );
        REQUIRE( p.check_right_bracket(std::string("{")) == false );
    }

    SECTION("check_precedence(std::string a, std::string b)")
    {
        REQUIRE( p.check_precedence(std::string("+"), std::string("*")) == false );
        REQUIRE( p.check_precedence(std::string("*"), std::string("/")) == true );
        REQUIRE( p.check_precedence(std::string("/"), std::string("/")) == true );
        REQUIRE( p.check_precedence(std::string("-"), std::string("*")) == false );
    }
}

TEST_CASE("Testing Parse implementation")
{
    ShuntingYard sy1(std::string("4+3"));
    std::queue<std::string> out1 = sy1.parsing();
    std::queue<std::string> out2;
    out2.push("4");
    out2.push("3");
    out2.push("+");


    for (int i = 0; i < out1.size(); i++)
    {
        REQUIRE (out1.front() ==  out2.front() );
        out1.pop();
        out2.pop();
    }

    ShuntingYard sy2(std::string("3 + 4 * 2 / (1 - 5)"));
    std::queue<std::string> out3 = sy2.parsing();
    std::queue<std::string> out4;
    out4.push("3");
    out4.push("4");
    out4.push("2");
    out4.push("*");
    out4.push("1");
    out4.push("5");
    out4.push("-");
    out4.push("/");
    out4.push("+");

    for (int i = 0; i < out1.size(); i++)
    {
        REQUIRE (out3.front() ==  out4.front() );
        out3.pop();
        out4.pop();
    }

}
