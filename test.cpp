#define CATCH_CONFIG_MAIN
#include "test/catch.hpp"
#include "lib/Parser.hpp"

TEST_CASE("Testing Parse implementation", "[parse]")
{
    Parser p;
    REQUIRE( p.check_number(std::string("3")) == true );
}
