find_package(Catch2 3 REQUIRED)
add_executable(integration_test ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)

# link to catch2 library
target_link_libraries(integration_test PRIVATE Catch2::Catch2WithMain)
#target_link_libraries(custom-main-tests PRIVATE Catch2::Catch2)

add_test(NAME integration_test COMMAND integration_test)
