cmake_minimum_required(VERSION 3.20)
project(cmake_arduino_cli_experiment)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)
