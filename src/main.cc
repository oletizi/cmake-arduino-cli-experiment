#include <iostream>
#include <juce_core/juce_core.h>
#include <juce_audio_devices/juce_audio_devices.h>

namespace juce {

    class MyApp : public JUCEApplicationBase, public MidiInputCallback {
    public:
        const String getApplicationName() { return "Thingy!"; }

        const String getApplicationVersion() { return "0.1"; }

        bool moreThanOneInstanceAllowed() { return false; }

        ~MyApp() override {
            std::cout << "Destructor.\n";
        }

        void handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message) override {
            std::cout << "Midi message!" << std::endl;
        }

        void initialise(const String &commandLineParameters) override {
            printf("Initializing!\n");
            auto devices = MidiInput::getAvailableDevices();
            printf("Device count: %d\n", devices.size());
            for (int i=0; i< devices.size(); i++) {
                auto device = devices[i];
                std::cout << "Device[" << i << "]: " << device.name << std::endl;
                if (device.name.contains("IAC")) {
                    std::cout << "It's the IAC Driver!!! Trying to connect!\n";
                    auto connected = MidiInput::openDevice(device.identifier, this);
                    std::cout << "Connected to " << connected->getName() << std::endl;
                }
            }
        }

        void shutdown() override {
            std::cout << "Shutting down.\n";
        }

        void anotherInstanceStarted(const String &commandLine) override {
            std::cout << "Another instance started!\n";
        }

        void systemRequestedQuit() override {
            std::cout << "System requested quit.\n";
        }

        void suspended() override {
            std::cout << "Suspended.\n";
        }

        void resumed() override {
            std::cout << "Resumed.\n";
        }

        void
        unhandledException(const std::exception *exception, const String &sourceFilename, int lineNumber) override {
            std::cout << "Exception: " << exception << "; file: " << sourceFilename << ": " << lineNumber << std::endl;
        }
    };
}

//int main(int argc, char *argv[]) {
//    std::cout << "Hello, World!" << std::endl;
//    return 0;
//}
START_JUCE_APPLICATION (juce::MyApp)