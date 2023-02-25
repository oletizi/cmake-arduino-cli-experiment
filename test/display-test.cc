//
// Created by Orion Letizi on 2/5/23.
//
#include <gtest/gtest.h>
#include "thingy_display.h"

namespace thingy::display {
    TEST(DisplayTestSuite, TestBasics) {
        Display *d;
        d = new SerialDisplay();
        EXPECT_NE(d, nullptr);
    }
}
