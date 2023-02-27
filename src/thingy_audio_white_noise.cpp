//
// Created by Orion Letizi on 2/26/23.
//
#include "thingy_audio_white_noise.h"
namespace thingy {
    void WhiteNoise::update(void)  {
        audio_block_t *block;
        block = allocate();
        if (block) {
            for (uint32_t i=0; i < AUDIO_BLOCK_SAMPLES; i++) {
                // fill buffer with white noise
               uint16_t value = rand();
               block->data[i] = value;
            }
            transmit(block);
            release(block);
        }
    }
}
