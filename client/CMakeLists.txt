add_executable(client
        ${CMAKE_CURRENT_SOURCE_DIR}/src/client.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/utils.cpp
)

target_include_directories(client
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/client>
        $<INSTALL_INTERFACE:include/client>
)

target_compile_options(client PRIVATE -Wall -Wextra -Wpedantic)

set_target_properties(client PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
)

