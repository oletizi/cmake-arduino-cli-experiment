//
// Created by Orion Letizi on 2/13/23.
//
#ifndef THINGY_MIDI_H
#define THINGY_MIDI_H

#include <iostream>
#include <juce_core/juce_core.h>
#include <juce_audio_devices/juce_audio_devices.h>

namespace thingy {
    namespace midi {
        using namespace std;
        using namespace juce;

        class MidiBroker : public MidiInputCallback {
            string name = "MidiBroker: ";
            std::unique_ptr<MidiInput> inputs[128] = {};
        public:
            void connectToInput() {
                auto devices = MidiInput::getAvailableDevices();
                cout << this->name << "MIDI input device count: " << devices.size() << endl;
                for (int i = 0; i < devices.size(); i++) {
                    auto device = devices[i];
                    cout << this->name << "Midi input device[" << i << "]: " << device.name << endl;

                    auto midiInput = MidiInput::openDevice(device.identifier, this);
                    //inputs.add(midiInput);
                    cout << this->name << "Connected to " << midiInput->getName() << endl;
                    midiInput->start();
                    inputs[i] = move(midiInput);
                }
            }

            void handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message) override {
                cout << this->name << "source: " << source << " ch: " << message.getChannel();
                cout << " type: " << message.getMetaEventType() << endl;
            }

            void handlePartialSysexMessage(MidiInput *source,
                                           const uint8 *messageData,
                                           int numBytesSoFar,
                                           double timestamp) override {
                cout << this->name << "Partial Sysex! source: " << source << "; data: " << messageData;
                cout << "; numBytesSoFar: " << numBytesSoFar << "; timestamp: " << timestamp;
                cout << endl;
            }

        };
    }
}

#endif //THINGY_MIDI_H
