set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES
        main.cc
        loop.h
        loop.cpp
        display.h
        display.cc
        Arduino_local.h
        )

add_executable(${BINARY}_run ${SOURCES})
target_link_libraries(${BINARY}_run INTERFACE arduino-dummy)


add_library(${BINARY}_lib STATIC ${SOURCES})
target_link_libraries(${BINARY}_lib INTERFACE arduino-dummy)