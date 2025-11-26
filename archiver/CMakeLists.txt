# Require a minimum version of cmake
cmake_minimum_required(VERSION 4.0)

# Set project name
project(archiver)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set optimizations
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

# Set target and sources
set(SOURCES
    src/main.cpp
    src/operation.cpp
    src/help.cpp
    include/program.hpp
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Specify required features for compiling
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Specify optimization options
target_compile_options(${PROJECT_NAME} PRIVATE -march=native)

add_custom_command(
  TARGET "${PROJECT_NAME}" POST_BUILD
  COMMAND $<$<CONFIG:release>:${CMAKE_STRIP}>
  ARGS -s $<TARGET_FILE:${PROJECT_NAME}>
)
