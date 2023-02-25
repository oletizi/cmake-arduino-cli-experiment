//
// Created by Orion Letizi on 2/25/23.
//

#ifndef THINGY_THINGY_MIDI_LISTENER_H
#define THINGY_THINGY_MIDI_LISTENER_H
#include "thingy_midi_message.h"
namespace thingy {
    class MidiListener {
        virtual void handleMessage(MidiMessage message) = 0;
    };
}
#endif //THINGY_THINGY_MIDI_LISTENER_H
