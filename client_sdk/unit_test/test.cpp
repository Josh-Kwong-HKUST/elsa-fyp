#include <catch2/catch_test_macros.hpp>
#include "../include/fix_client.h"
#include <iostream>

int test_fix() {
    try {
        auto client = new FixClient("/home/josh/repo/elsa-fyp/client_sdk/example_config_client.cfg");
        client->connect();
        return 0;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
}

TEST_CASE("QuickFIX unit_test", "[QuickFIX]") {
    REQUIRE( test_fix() == 0 );
}