find_package(Catch2 3 REQUIRED)
include(Catch)

add_executable(unit_test ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)

# link to catch2 library
target_link_libraries(unit_test PRIVATE Catch2::Catch2WithMain)
#target_link_libraries(custom-main-tests PRIVATE Catch2::Catch2)

#add_test(NAME unit_test COMMAND unit_test)

catch_discover_tests(unit_test)