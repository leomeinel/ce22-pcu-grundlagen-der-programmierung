# Require a minimum version of cmake
cmake_minimum_required(VERSION 4.0)

# Set project name
project(archiver)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set ide options
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set optimizations
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

# Set target and sources
set(SOURCES
    src/main.cpp
    src/cli.cpp
    src/filesystem.cpp
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Use kebab-case for OUTPUT_NAME
string(REPLACE "_" "-" OUTPUT_NAME "${PROJECT_NAME}")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "${OUTPUT_NAME}")

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Specify optimization options
target_compile_options(${PROJECT_NAME} PRIVATE -march=native)

add_custom_command(
  TARGET "${PROJECT_NAME}" POST_BUILD
  COMMAND $<$<CONFIG:Release>:${CMAKE_STRIP}>
  ARGS -s $<TARGET_FILE:${PROJECT_NAME}>
)
