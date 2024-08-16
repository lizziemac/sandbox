# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER g++)

# Set the project name
project(server)

# Add the source files to the project
add_executable(server_app main.cpp)

# Add any additional dependencies or libraries here
# gio
find_package(PkgConfig REQUIRED)
pkg_check_modules(GIO REQUIRED gio-2.0)
target_link_libraries(server_app PRIVATE ${GIO_LIBRARIES})
target_include_directories(server_app PRIVATE ${GIO_INCLUDE_DIRS})
