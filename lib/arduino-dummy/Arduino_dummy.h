//
// Dummy Arduino header for CMake.
//

#ifndef ARDUINO_DUMMY_H
#define ARDUINO_DUMMY_H

#ifdef TARGET_NATIVE

#include <string>
#include <iostream>

#define OUTPUT 0
#define HIGH 0
#define LOW 0

void delay(int i);
void digitalWrite(int i, int i1);
void pinMode(int i, int i1);

void delay(int i) {}
void digitalWrite(int i, int i1) {}
void pinMode(int i, int i1) {}

class Print {
public:
    static size_t println(std::string msg);
};

size_t Print::println(std::string msg) {
    std::cout << msg << '\n';
    return msg.length();
}


Print Serial;

#else // TARGET_NATIVE not defined (so, we're building for an Arduino
#include <Arduino.h>
#endif // TARGET_NATIVE

#endif // ARDUINO_DUMMY
