cmake_minimum_required(VERSION 3.16)
project(hello VERSION 0.1.0 LANGUAGES CXX)

# Collect sources from src/
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
file(GLOB_RECURSE PROJECT_SOURCES
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/*.cc"
    "${SRC_DIR}/*.cxx"
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${SRC_DIR})

# Set C++20 standard
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
# Set compiler warnings
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
)
