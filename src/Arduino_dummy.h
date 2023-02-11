//
// Created by Orion Letizi on 2/11/23.
//

#ifndef CMAKE_ARDUINO_CLI_EXPERIMENT_ARDUINO_DUMMY_H
#define CMAKE_ARDUINO_CLI_EXPERIMENT_ARDUINO_DUMMY_H

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
#else // TARGET_NATIVE not defined (so, we're building for an Arduino
#include <Arduino.h>
#endif // TARGET_NATIVE

#endif //CMAKE_ARDUINO_CLI_EXPERIMENT_ARDUINO_DUMMY_H
