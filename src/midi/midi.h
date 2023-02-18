//
// Created by Orion Letizi on 2/13/23.
//

#ifndef THINGY_MIDI_H
#define THINGY_MIDI_H

namespace thingy::midi {
    /* Aliases for callbacks from MIDI.h in the Arduino MIDI library */

    using NoteOnCallback = void (*)(Channel channel, byte note, byte velocity);


    class MidiReceiver {
    public:
        virtual void setHandleNoteOn(NoteOnCallback fptr) = 0;
    };
}


#endif //THINGY_MIDI_H
