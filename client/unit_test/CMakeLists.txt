find_package(Catch2 3 REQUIRED)
include(Catch)

add_executable(unit_test test.cpp)

# link to catch2 library
target_link_libraries(unit_test PRIVATE Catch2::Catch2WithMain)

catch_discover_tests(unit_test)