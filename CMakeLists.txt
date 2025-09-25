cmake_minimum_required(VERSION 4.0)
project(elsa_fyp)

find_package(Catch2 3 REQUIRED)
# link to catch2 library
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(custom-main-tests PRIVATE Catch2::Catch2)

set(CMAKE_CXX_STANDARD 23)
