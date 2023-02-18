//
// Created by Orion Letizi on 2/13/23.
//

#ifndef THINGY_MIDI_H
#define THINGY_MIDI_H

namespace thingy {
    namespace midi {
#ifdef TARGET_NATIVE
#include <iostream>
#include <juce_audio_devices/juce_audio_devices.h>
        using namespace std;
        using namespace juce;
        class MidiBroker : public MidiInputCallback {
            std::unique_ptr<MidiInput> midiInput;
            void handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message) override {
                cout << "ch: " << message.getChannel();
                cout << " type: " << message.getMetaEventType() << endl;
            }
        };
#else//ARDUINO
        /* Aliases for callbacks from MIDI.h in the Arduino MIDI library */

        using NoteOnCallback = void (*)(Channel channel, byte note, byte velocity);


        class MidiReceiver {
        public:
            virtual void setHandleNoteOn(NoteOnCallback fptr) = 0;
        };

#endif //TARGET_NATIVE
    }
}

#endif //THINGY_MIDI_H
