#define CATCH_CONFIG_MAIN
#include "thirdparty/catch2.hpp"

TEST_CASE("Test 1", "[test1]") {
    REQUIRE(1 == 1);
}