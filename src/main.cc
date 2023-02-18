#include <iostream>
#include <juce_core/juce_core.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include "midi/midi.h"

namespace juce {
    using namespace std;

    class MyApp : public JUCEApplicationBase, Timer {
        //unique_ptr<MidiOutput> midiOutput;
        unique_ptr<MidiOutput> outputs[128] = {}; // this is just for experimentation.
        thingy::midi::MidiBroker *midiInputCallback;

    public:
        const String getApplicationName() override { return "Thingy!"; }

        const String getApplicationVersion() override { return "0.1"; }

        bool moreThanOneInstanceAllowed() override { return false; }

        ~MyApp() override {
            std::cout << "Destructor.\n";
        }

        void connectToOutput() {
            auto devices = MidiOutput::getAvailableDevices();
            cout << "MIDI output device count: " << devices.size() << endl;
            for (int i = 0; i < devices.size(); i++) {
                auto device = devices[i];
                cout << "Connecting to midi device: " << device.name << endl;
                //this->midiOutput = MidiOutput::openDevice(device.identifier);
                auto midiOutput = MidiOutput::openDevice(device.identifier);
                outputs[i] = move(midiOutput);
            }
        }

        void initialise(const String &commandLineParameters) override {
            cout << "Initializing!\n";
            cout << "cmdline: " << commandLineParameters << endl;
            cout << "Starting timer...\n";
            Timer::startTimer(1000);
            connectToOutput();
            midiInputCallback = new thingy::midi::MidiBroker();
            midiInputCallback->connectToInput();
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
            for (int i=0; i<127; i++) {
                if (this->outputs[i]) {
                    this->outputs[i]->sendMessageNow(msg);
                }
            }
        }
    };
}

START_JUCE_APPLICATION (juce::MyApp)