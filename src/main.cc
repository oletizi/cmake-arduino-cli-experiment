#include <iostream>
#include <juce_core/juce_core.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include "midi/midi.h"
#include "synth/synth.h"

namespace juce {
    using namespace std;

    class MyApp : public JUCEApplicationBase, Timer {
        vector<unique_ptr<MidiOutput>> outputs;
        thingy::midi::MidiBroker *midiBroker;

    public:
        const String getApplicationName() override { return "Thingy!"; }

        const String getApplicationVersion() override { return "0.1"; }

        bool moreThanOneInstanceAllowed() override { return false; }

        ~MyApp() override {
            std::cout << "Destructor.\n";
        }

        void connectToOutputs() {
            auto devices = MidiOutput::getAvailableDevices();
            cout << "MIDI output device count: " << devices.size() << endl;
            for (int i = 0; i < devices.size(); i++) {
                auto device = devices[i];
                cout << "Connecting to midi device: " << device.name << endl;
                //this->midiOutput = MidiOutput::openDevice(device.identifier);
                auto midiOutput = MidiOutput::openDevice(device.identifier);
                //outputs[i] = move(midiOutput);
                outputs.push_back(move(midiOutput));
            }
        }

        void initialise(const String &commandLineParameters) override {
            cout << "Initializing!\n";
            cout << "cmdline: " << commandLineParameters << endl;
            cout << "Starting timer...\n";
            //Timer::startTimer(1000);
            connectToOutputs();
            midiBroker = new thingy::midi::MidiBroker();
            midiBroker->connectToInputs();

            auto synth = new thingy::synth::Synth(midiBroker);
        }

        void shutdown() override {
            cout << "Shutting down.\n";
        }

        void anotherInstanceStarted(const String &commandLine) override {
            cout << "Another instance started! commandLine: " << commandLine << endl;
        }

        void systemRequestedQuit() override {
            cout << "System requested quit.\n";
        }

        void suspended() override {
            cout << "Suspended.\n";
        }

        void resumed() override {
            cout << "Resumed.\n";
        }

        void
        unhandledException(const std::exception *exception, const String &sourceFilename, int lineNumber) override {
            cout << "Exception: " << exception << "; file: " << sourceFilename << ": " << lineNumber << endl;
        }

        void timerCallback() override {
            auto msg = MidiMessage::noteOn(1, 10, .1f);
            for (size_t i=0; i<outputs.size(); i++) {
                if (this->outputs.at(i)) {
                    this->outputs.at(i)->sendMessageNow(msg);
                }
            }
        }
    };
}

START_JUCE_APPLICATION (juce::MyApp)