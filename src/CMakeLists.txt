set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES
        main.cc
        loop.h
        loop.cpp
        display.h
        display.cc
        Arduino_dummy.h)

add_executable(${BINARY}_run ${SOURCES})
add_library(${BINARY}_lib STATIC ${SOURCES})