cmake_minimum_required(VERSION 4.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(elsa_fyp_client_sdk)

add_library(client_sdk
        ${CMAKE_CURRENT_SOURCE_DIR}/src/client.cpp
        src/application.cpp
        include/application.h
)
target_include_directories(client_sdk
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_options(client_sdk PRIVATE -Wall -Wextra -Wpedantic -finline-functions)

set_target_properties(client_sdk PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
)
# find packages required for QuickFIX
find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)
find_package(LibXml2 REQUIRED)
find_package(ZLIB REQUIRED)

# Find QuickFIX via pkg-config
pkg_check_modules(QuickFIX REQUIRED quickfix)

# Link QuickFIX
target_link_libraries(client_sdk PUBLIC
        ${QuickFIX_LIBRARIES}
        Threads::Threads
        LibXml2::LibXml2
        ZLIB::ZLIB
)
target_include_directories(client_sdk PUBLIC ${QuickFIX_INCLUDE_DIRS})
target_compile_definitions(client_sdk PUBLIC ${QuickFIX_CFLAGS_OTHER})

if(BUILD_TESTS)
    add_subdirectory(unit_test)
endif()
