cmake_minimum_required(VERSION 3.20)
project(cmake_arduino_cli_experiment)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(TARGET_NATIVE)


include_directories(src lib/arduino-dummy)

add_subdirectory(lib/googletest)
add_subdirectory(lib/arduino-dummy)
add_subdirectory(src)
add_subdirectory(test)
