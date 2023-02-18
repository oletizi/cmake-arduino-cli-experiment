set(BINARY ${CMAKE_PROJECT_NAME})

set(SOURCES
        display/display.h
        display/display.cc
        loop.h
        loop.cpp
        midi/midi.h
        )

#add_executable(${BINARY}_run ${SOURCES})
#target_link_libraries(${BINARY}_run INTERFACE arduino-dummy)
#
#
add_library(${LIB_TARGET} STATIC ${SOURCES})
target_link_libraries(${LIB_TARGET} PUBLIC libarduino-dummy)
target_include_directories(${LIB_TARGET} PUBLIC .)


juce_add_console_app(${JUCE_TARGET}
        PRODUCT_NAME ${JUCE_TARGET})

target_sources(${JUCE_TARGET} PRIVATE main.cc ${SOURCES})
target_link_libraries(${JUCE_TARGET}
        PRIVATE
        # ConsoleAppData            # If you'd created a binary data target, you'd link to it here
        juce::juce_core
        juce::juce_audio_devices
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
        libarduino-dummy
        )
juce_generate_juce_header(${JUCE_TARGET})