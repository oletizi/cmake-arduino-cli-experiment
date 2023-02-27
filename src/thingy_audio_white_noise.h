//
// Created by Orion Letizi on 2/26/23.
//

#ifndef THINGY_THINGY_AUDIO_WHITE_NOISE_H
#define THINGY_THINGY_AUDIO_WHITE_NOISE_H

#include "thingy_audio.h"

namespace thingy {
    class WhiteNoise : public AudioStream {

    public:
        WhiteNoise() : AudioStream(0, NULL) {}

    private:
        void update(void) override;
    };

}

#endif //THINGY_THINGY_AUDIO_WHITE_NOISE_H
