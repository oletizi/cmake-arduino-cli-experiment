#include <iostream>
#include <juce_core/juce_core.h>
#include <juce_audio_devices/juce_audio_devices.h>

namespace juce {
    using namespace std;

    class MyApp : public JUCEApplicationBase, public MidiInputCallback, Timer {
        std::unique_ptr<MidiOutput> midiOutput;
        std::unique_ptr<MidiInput> midiInput;
        String inputDeviceName = "Arturia KeyStep";
        String outputDeviceName = "IAC";

    public:
        const String getApplicationName() { return "Thingy!"; }

        const String getApplicationVersion() { return "0.1"; }

        bool moreThanOneInstanceAllowed() { return false; }

        ~MyApp() override {
            std::cout << "Destructor.\n";
        }

        void handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message) override {
            cout << "Midi message!" << endl;
        }
        void handlePartialSysexMessage (MidiInput* source,
                                        const uint8* messageData,
                                        int numBytesSoFar,
                                        double timestamp) override {
            cout << "Partial Sysex!" << endl;
        }

        void connectToOutput() {
            auto devices = MidiOutput::getAvailableDevices();
            cout << "MIDI output device count: " << devices.size() << endl;
            for (int i = 0; i < devices.size(); i++) {
                auto device = devices[i];
                if (device.name.contains(this->outputDeviceName)) {
                    cout << "Connecting to midi device: " << device.name << endl;
                    this->midiOutput = MidiOutput::openDevice(device.identifier);
                    break;
                }
            }
        }

        void connectToInput() {
            auto devices = MidiInput::getAvailableDevices();
            cout << "MIDI input device count: " << devices.size() << endl;

            for (int i = 0; i < devices.size(); i++) {
                auto device = devices[i];
                cout << "Midi input device[" << i << "]: " << device.name << endl;
                if (device.name.contains(this->inputDeviceName)) {
                    cout << "It's my device: " << this->inputDeviceName << ". Trying to connect!\n";
                    this->midiInput = MidiInput::openDevice(device.identifier, this);
                    cout << "Connected to " << this->midiInput->getName() << endl;
                }
            }
        }

        void initialise(const String &commandLineParameters) override {
            cout << "Initializing!\n";
            cout << "Starting timer...\n";
            Timer::startTimer(1000);
            connectToInput();
            connectToOutput();
        }

        void shutdown() override {
            cout << "Shutting down.\n";
        }

        void anotherInstanceStarted(const String &commandLine) override {
            cout << "Another instance started!\n";
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
            this->midiOutput->sendMessageNow(msg);
        }
    };
}

START_JUCE_APPLICATION (juce::MyApp)