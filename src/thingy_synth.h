//
// Created by Orion Letizi on 2/22/23.
//

#ifndef THINGY_THINGY_SYNTH_H
#define THINGY_THINGY_SYNTH_H

#include <iostream>
#include "thingy_midi.h"

namespace thingy {

    class Synth : public ThingyMidiListener {
    public:
        explicit Synth(thingy::ThingyMidiPublisher *midiPublisher) {
            std::cout << "Synth: MidiBroker: " << midiPublisher;
            midiPublisher->addMidiListener(this);
        }

        void handleMessage(ThingyMidiMessage message) override;
    };
}
#endif //THINGY_THINGY_SYNTH_H
