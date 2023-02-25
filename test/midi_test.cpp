//
// Created by Orion Letizi on 2/25/23.
//

#include <gtest/gtest.h>
#include "thingy_midi.h"

namespace thingy {
    TEST(MidiTestSuite, TestBasics) {
        ThingyMidiMessage m{0};
        EXPECT_EQ(m.channel, 0);
    }

    class MockMidiListener : public ThingyMidiListener {
        void handleMessage(ThingyMidiMessage message) override;
    };

    void MockMidiListener::handleMessage(ThingyMidiMessage message) {}

    TEST(MidiTestSuite, TestMidiBroker) {
        auto b = new MidiBroker();
        juce::MidiInput *source = nullptr;
        juce::MidiMessage juceMessage;
        MockMidiListener mockListener;
        b->addMidiListener(&mockListener);
        b->handleIncomingMidiMessage(source, juceMessage);
    }
}