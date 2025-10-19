find_package(Catch2 3 REQUIRED)
include(Catch)

add_executable(integration_test test.cpp)

# link to catch2 library
target_link_libraries(integration_test PRIVATE Catch2::Catch2WithMain)

catch_discover_tests(integration_test)