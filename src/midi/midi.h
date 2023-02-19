//
// Created by Orion Letizi on 2/13/23.
//
#ifndef THINGY_MIDI_H
#define THINGY_MIDI_H

#ifdef TARGET_NATIVE

#include <iostream>
#include <juce_core/juce_core.h>
#include <juce_audio_devices/juce_audio_devices.h>


namespace thingy::midi {
    using namespace std;
    using namespace juce;

    // Type definitions from the Arduion midi library
    typedef byte Channel;

    // Callback aliases from the Arduino midi library
    using ErrorCallback = void (*)(int8_t);
    using NoteOffCallback = void (*)(Channel channel, byte note, byte velocity);
    using NoteOnCallback = void (*)(Channel channel, byte note, byte velocity);
    using AfterTouchPolyCallback = void (*)(Channel channel, byte note, byte velocity);
    using ControlChangeCallback = void (*)(Channel channel, byte, byte);
    using ProgramChangeCallback = void (*)(Channel channel, byte);
    using AfterTouchChannelCallback = void (*)(Channel channel, byte);
    using PitchBendCallback = void (*)(Channel channel, int);
    using SystemExclusiveCallback = void (*)(byte *array, unsigned size);
    using TimeCodeQuarterFrameCallback = void (*)(byte data);
    using SongPositionCallback = void (*)(unsigned beats);
    using SongSelectCallback = void (*)(byte songnumber);
    using TuneRequestCallback = void (*)(void);
    using ClockCallback = void (*)(void);
    using StartCallback = void (*)(void);
    using TickCallback = void (*)(void);
    using ContinueCallback = void (*)(void);
    using StopCallback = void (*)(void);
    using ActiveSensingCallback = void (*)(void);
    using SystemResetCallback = void (*)(void);

    class MidiBroker : public MidiInputCallback {
        string name = "MidiBroker: ";
        vector<unique_ptr<MidiInput>> inputs;
    public:

    public:
        inline void setHandleMessage(void (*fptr)(const MidiMessage &)) { mMessageCallback = fptr; };

        inline void setHandleError(ErrorCallback fptr) { mErrorCallback = fptr; }

        inline void setHandleNoteOff(NoteOffCallback fptr) { mNoteOffCallback = fptr; }

        inline void setHandleNoteOn(NoteOnCallback fptr) { mNoteOnCallback = fptr; }

        inline void setHandleAfterTouchPoly(AfterTouchPolyCallback fptr) { mAfterTouchPolyCallback = fptr; }

        inline void setHandleControlChange(ControlChangeCallback fptr) { mControlChangeCallback = fptr; }

        inline void setHandleProgramChange(ProgramChangeCallback fptr) { mProgramChangeCallback = fptr; }

        inline void setHandleAfterTouchChannel(AfterTouchChannelCallback fptr) { mAfterTouchChannelCallback = fptr; }

        inline void setHandlePitchBend(PitchBendCallback fptr) { mPitchBendCallback = fptr; }

        inline void setHandleSystemExclusive(SystemExclusiveCallback fptr) { mSystemExclusiveCallback = fptr; }

        inline void
        setHandleTimeCodeQuarterFrame(TimeCodeQuarterFrameCallback fptr) { mTimeCodeQuarterFrameCallback = fptr; }

        inline void setHandleSongPosition(SongPositionCallback fptr) { mSongPositionCallback = fptr; }

        inline void setHandleSongSelect(SongSelectCallback fptr) { mSongSelectCallback = fptr; }

        inline void setHandleTuneRequest(TuneRequestCallback fptr) { mTuneRequestCallback = fptr; }

        inline void setHandleClock(ClockCallback fptr) { mClockCallback = fptr; }

        inline void setHandleStart(StartCallback fptr) { mStartCallback = fptr; }

        inline void setHandleTick(TickCallback fptr) { mTickCallback = fptr; }

        inline void setHandleContinue(ContinueCallback fptr) { mContinueCallback = fptr; }

        inline void setHandleStop(StopCallback fptr) { mStopCallback = fptr; }

        inline void setHandleActiveSensing(ActiveSensingCallback fptr) { mActiveSensingCallback = fptr; }

        inline void setHandleSystemReset(SystemResetCallback fptr) { mSystemResetCallback = fptr; }

    private:
        void (*mMessageCallback)(const MidiMessage &message) = nullptr;

        ErrorCallback mErrorCallback = nullptr;
        NoteOffCallback mNoteOffCallback = nullptr;
        NoteOnCallback mNoteOnCallback = nullptr;
        AfterTouchPolyCallback mAfterTouchPolyCallback = nullptr;
        ControlChangeCallback mControlChangeCallback = nullptr;
        ProgramChangeCallback mProgramChangeCallback = nullptr;
        AfterTouchChannelCallback mAfterTouchChannelCallback = nullptr;
        PitchBendCallback mPitchBendCallback = nullptr;
        SystemExclusiveCallback mSystemExclusiveCallback = nullptr;
        TimeCodeQuarterFrameCallback mTimeCodeQuarterFrameCallback = nullptr;
        SongPositionCallback mSongPositionCallback = nullptr;
        SongSelectCallback mSongSelectCallback = nullptr;
        TuneRequestCallback mTuneRequestCallback = nullptr;
        ClockCallback mClockCallback = nullptr;
        StartCallback mStartCallback = nullptr;
        TickCallback mTickCallback = nullptr;
        ContinueCallback mContinueCallback = nullptr;
        StopCallback mStopCallback = nullptr;
        ActiveSensingCallback mActiveSensingCallback = nullptr;
        SystemResetCallback mSystemResetCallback = nullptr;

    public:
        // Connect to all the available midi inputs
        void connectToInputs() {
            auto devices = MidiInput::getAvailableDevices();
            cout << this->name << "MIDI input device count: " << devices.size() << endl;
            for (int i = 0; i < devices.size(); i++) {
                auto device = devices[i];
                cout << this->name << "Midi input device[" << i << "]: " << device.name << endl;

                auto midiInput = MidiInput::openDevice(device.identifier, this);
                //inputs.add(midiInput);
                cout << this->name << "Connected to " << midiInput->getName() << endl;
                midiInput->start();
                inputs.push_back(move(midiInput));
            }
        }

        // Handle incoming midi messages and dispatch them to callbacks
        void handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message) override {
            byte channel = (byte) message.getChannel();
            cout << this->name << "source: " << source->getName() << " ch: " << message.getChannel();
            if (message.isNoteOn()) {
                cout << "; note on : " << message.getNoteNumber();
                cout << "; velocity : " << (int) message.getVelocity();
                cout << "; f velocity: " << message.getFloatVelocity();
                if (mNoteOnCallback) {
                    mNoteOnCallback((byte) message.getChannel(), (byte) message.getNoteNumber(),
                                    (byte) message.getVelocity());
                }
            }
            if (message.isNoteOff()) {
                cout << "; note off: " << message.getNoteNumber();
                if (mNoteOffCallback) {
                    mNoteOffCallback(channel, (byte) message.getNoteNumber(), (byte) message.getVelocity());
                }
            }
            cout << endl;
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
#else // Arduino implementation
// Implement Me!
#endif //TARGET_NATIVE
#endif //THINGY_MIDI_H
