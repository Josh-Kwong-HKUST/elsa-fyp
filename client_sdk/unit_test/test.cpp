#include <catch2/catch_test_macros.hpp>
#include "../include/application.h"
#include "../include/client.h"

int test_fix() {
    try {
        auto app = new Application();
        return 0;
    } catch (std::exception& e) {
        return -1;
    }
}

TEST_CASE("QuickFIX unit_test", "[QuickFIX]") {
    REQUIRE( Client::add(1, 2) == 3 );
    REQUIRE( test_fix() == 0 );
}