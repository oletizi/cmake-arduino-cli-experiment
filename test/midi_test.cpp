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
    public:
        std::vector<ThingyMidiMessage> handleMessageCalls;
        void onMidiMessage(ThingyMidiMessage message) override {
            this->handleMessageCalls.push_back(message);
        }
    };

    TEST(MidiTestSuite, TestMidiPublisher) {
        auto *publisher = new ThingyMidiPublisher();
        ThingyMidiMessage message = {};
        auto listener = new MockMidiListener();
        publisher->addMidiListener(listener);
        publisher->onMidiMessage(message);
        EXPECT_EQ(1, listener->handleMessageCalls.size());
    }
}