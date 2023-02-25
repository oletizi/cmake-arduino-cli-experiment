//
// Created by Orion Letizi on 2/5/23.
//
#include <iostream>
#include "thingy_display.h"

namespace thingy::display {
    void SerialDisplay::print(std::string msg) {
        std::cout << msg;
    }
}