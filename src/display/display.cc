//
// Created by Orion Letizi on 2/5/23.
//
#include <iostream>
#include "display.h"

namespace thingy::display {
    void SerialDisplay::print(std::string msg) {
        std::cout << msg;
    }
}