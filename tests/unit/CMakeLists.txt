find_package(Catch2 3 REQUIRED)
# link to catch2 library
target_link_libraries(unit_test PRIVATE Catch2::Catch2WithMain)
#target_link_libraries(custom-main-tests PRIVATE Catch2::Catch2)

add_executable(unit_test test.cpp)