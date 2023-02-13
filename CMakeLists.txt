cmake_minimum_required(VERSION 3.20)

file(READ .project-name PROJECT_NAME)
file(READ .project-version PROJECT_VERSION)
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 17)

set(JUCE_TARGET ${CMAKE_PROJECT_NAME}_juce)
set(LIB_TARGET ${CMAKE_PROJECT_NAME}_lib)
set(TEST_TARGET ${CMAKE_PROJECT_NAME}_test)

# This is a switch used to swap t dummy Arduino header in lib/arduino-dummy for the real Arduino header
# when compiling on a native system.
add_compile_definitions(TARGET_NATIVE)

#include_directories(src lib/arduino-dummy)

add_subdirectory(lib/libarduino-dummy)
add_subdirectory(lib/googletest)
add_subdirectory(lib/juce)
add_subdirectory(src)
add_subdirectory(test)