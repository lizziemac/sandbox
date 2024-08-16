# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER g++)

# Set the project name
project(notifier)

# Add the source files to the project
add_executable(notifier_app main.cpp)

# Add any additional dependencies or libraries here
# TODO