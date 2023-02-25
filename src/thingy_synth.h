//
// Created by Orion Letizi on 2/22/23.
//

#ifndef THINGY_THINGY_SYNTH_H
#define THINGY_THINGY_SYNTH_H

#include <iostream>
#include "thingy_midi.h"

namespace thingy {

    class Synth {
    public:
        explicit Synth(thingy::MidiBroker *midiBroker) {
            std::cout << "Synth: MidiBroker: " << midiBroker;
        }
    };
}
#endif //THINGY_THINGY_SYNTH_H
