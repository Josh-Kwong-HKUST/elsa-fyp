add_executable(matching_engine
        ${CMAKE_CURRENT_SOURCE_DIR}/src/matching_engine.cpp
)

target_include_directories(matching_engine
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_options(matching_engine PRIVATE -Wall -Wextra -Wpedantic)

set_target_properties(matching_engine PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
)

if(BUILD_TESTS)
    add_subdirectory(unit_test)
endif()

