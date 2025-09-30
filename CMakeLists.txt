cmake_minimum_required(VERSION 4.0)
set(CMAKE_CXX_STANDARD 23)
project(elsa_fyp)

add_subdirectory(client)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()