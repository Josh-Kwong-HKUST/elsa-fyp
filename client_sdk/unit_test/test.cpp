#include <catch2/catch_test_macros.hpp>
#include <iostream>

#include "test_client.h"

int test_fix() {
    try {
        auto client = new TestClient("/home/josh/repo/elsa-fyp/client_sdk/example_config_client.cfg");
        client->connect(5);
        return 0;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
}

TEST_CASE("QuickFIX unit_test", "[QuickFIX]") {
    REQUIRE( test_fix() == 0 );
}