#include <iostream>
#include <juce_core/juce_core.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include "thingy_audio.h"
#include "thingy_midi.h"
#include "thingy_synth.h"

namespace juce {
    using namespace std;

    class MyApp : public JUCEApplicationBase, Timer {
        vector<unique_ptr<MidiOutput>> outputs;
        vector<MyAudioCallback *> audioCallbacks;
        thingy::MidiBroker *midiBroker;
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
            midiBroker = new thingy::MidiBroker();
            midiBroker->connectToInputs();

            //auto audioCallback = new MyAudioCallback("whee");
            auto adm = juce::AudioDeviceManager();
            const OwnedArray<AudioIODeviceType> &deviceTypes = adm.getAvailableDeviceTypes();
            cout << "Audio device types: size: " << deviceTypes.size() << endl;

            for (int i = 0; i < deviceTypes.size(); i++) {
                auto deviceType = deviceTypes.getUnchecked(i);

                cout << "Device type: [" << i << "]: " << deviceType->getTypeName() << endl;
                deviceType->scanForDevices();
                //deviceType->addListener(deviceListener);
                const StringArray &stringArray = deviceType->getDeviceNames();
                cout << "Device name count: " << stringArray.size() << endl;
                for (const auto &deviceName: stringArray) {
                    cout << deviceName << endl;
                    cout << "  Creating device named " << deviceName << endl;
                    AudioIODevice *audioDevice = deviceType->createDevice(deviceName, "");
                    cout << "  Created audio device: " << audioDevice->getName() << ": " << audioDevice << endl;

                    cout << "  Opening device..." << endl;
                    const String &open = audioDevice->open(0, 2, 48000, 512);
                    cout << "  RV: " << open << endl;

                    cout << "  Starting device..." << endl;
                    auto audioCallback = new MyAudioCallback(deviceName.toStdString());
                    this->audioCallbacks.push_back(audioCallback);
                    audioDevice->start(audioCallback);
                    cout << "  Started device." << endl;
                }
            }

            //auto device = adm.getCurrentAudioDevice();
            //cout << "Current audio device: " << device->getName() << endl;

            new thingy::Synth(midiBroker->getMidiPublisher());
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
            for (size_t i = 0; i < outputs.size(); i++) {
                if (this->outputs.at(i)) {
                    this->outputs.at(i)->sendMessageNow(msg);
                }
            }
        }
    };
}

START_JUCE_APPLICATION (juce::MyApp)