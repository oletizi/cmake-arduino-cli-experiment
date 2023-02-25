//
// Created by Orion Letizi on 2/25/23.
//

#include <gtest/gtest.h>
#include "thingy_midi_message.h"

namespace thingy {
    TEST(MidiTestSuite, TestBasics) {
        MidiMessage m;
        EXPECT_EQ(m.channel, 0);
    }
}