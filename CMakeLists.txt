# Set the minimum version of Cmake required
cmake_minimum_required(VERSION 3.23)

# Define the project
project(
    Automata
    VERSION 1.0
    DESCRIPTION "An automata used to simulate stuff."
    LANGUAGES CXX
)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)