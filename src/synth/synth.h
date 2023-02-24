//
// Created by Orion Letizi on 2/22/23.
//

#ifndef THINGY_SYNTH_H
#define THINGY_SYNTH_H

#include <iostream>
#include "../midi/midi.h"

namespace thingy::synth {

    class Synth {
    public:
        explicit Synth(thingy::midi::MidiBroker *midiBroker) {
            std::cout << "Synth: MidiBroker: " << midiBroker;
        }
    };
}
#endif //THINGY_SYNTH_H
