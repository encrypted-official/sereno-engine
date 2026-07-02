cmake_minimum_required(VERSION 3.22)

project(sereno-engine VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(SERENO_BUILD_SHARED "Build shared library" ON)

file(GLOB_RECURSE SERENO_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

if(SERENO_BUILD_SHARED)
    add_library(sereno SHARED ${SERENO_SOURCES})
else()
    add_library(sereno STATIC ${SERENO_SOURCES})
endif()

target_include_directories(
    sereno
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)

set_target_properties(
    sereno
    PROPERTIES
    OUTPUT_NAME "sereno"
)

add_executable(
    sereno-cli
    tests/cli.c
)

target_link_libraries(
    sereno-cli
    PRIVATE
    sereno
)

target_include_directories(
    sereno-cli
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/inc"
)