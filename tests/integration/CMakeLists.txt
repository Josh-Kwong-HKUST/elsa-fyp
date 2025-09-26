find_package(Catch2 3 REQUIRED)
add_executable(integration_test test.cpp)

# link to catch2 library
target_link_libraries(integration_test PRIVATE Catch2::Catch2WithMain)
#target_link_libraries(custom-main-tests PRIVATE Catch2::Catch2)

