#include <catch2/catch_test_macros.hpp>

#include "../src/limit_order_book.h"

TEST_CASE("Construction of limit order book", "[lob]") {
    LimitOrderBook book;
    REQUIRE( book.foo() == true );
}
