//
// Created by Orion Letizi on 2/11/23.
//

#ifndef CMAKE_ARDUINO_CLI_EXPERIMENT_ARDUINO_LOCAL_H
#define CMAKE_ARDUINO_CLI_EXPERIMENT_ARDUINO_LOCAL_H

#ifdef TARGET_NATIVE
#include <Arduino_dummy.h>
#else
#include <Arduino.h>
#endif //TARGET_NATIVE

#endif //CMAKE_ARDUINO_CLI_EXPERIMENT_ARDUINO_LOCAL_H
