# Require a minimum version of cmake
cmake_minimum_required(VERSION 4.0)

# Set project name
project(archiver)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add executable and specify sources
set(SOURCES
    src/main.cpp
    src/actions.cpp
    src/help.cpp
    src/states.cpp
    include/program.hpp
)
add_executable(archiver.out ${SOURCES})

# Specifies required features for compiling
target_compile_features(archiver.out PRIVATE cxx_std_23)

# Add include directories
target_include_directories(archiver.out PRIVATE include)
