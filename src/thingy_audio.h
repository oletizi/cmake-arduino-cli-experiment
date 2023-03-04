//
// Created by Orion Letizi on 2/25/23.
//


#ifdef TARGET_NATIVE

#ifndef THINGY_AUDIO_H
#define THINGY_AUDIO_H

#include <limits>
#include <Arduino_dummy.h>
#include <juce_audio_devices/juce_audio_devices.h>

namespace thingy {
    // convert float sample [-1..1] to int16
    int16_t sample_convert_float_to_int16(float s) {
        if (s > 0.0f) {
            return static_cast<int16_t>(s * std::numeric_limits<int16_t>::max());
        } else {
            return static_cast<int16_t>(-s * std::numeric_limits<int16_t>::min());
        }
    }

    // convert in16 sample to float [-1..1]
    float sample_convert_int16_to_float(int16_t s) {
        float sf = s / static_cast<float>( std::numeric_limits<int16_t>::max());
        //ASSERT_MSG( sf >= -1.0f && sf <= 1.0f, "Sample out of range" );

        return sf;
    }

    class MyAudioCallback : public juce::AudioIODeviceCallback {
        std::string myDeviceName;
        juce::Time checkpoint = juce::Time::getCurrentTime();
        int count = 0;
        int bitDepth = 0;
        double sampleRate = 0;
        float gain = 0.5;
    public:
        explicit MyAudioCallback(const std::string &deviceName) {
            myDeviceName = deviceName;
        }

        void audioDeviceAboutToStart(juce::AudioIODevice *device) override {
            std::cout << "Device starting  : " << device->getName() << std::endl;
            const juce::BigInteger &integer = device->getActiveOutputChannels();
            std::cout << "  Output channels: " << integer.toString(10, 1) << std::endl;
            std::cout << "  Bit depth      : " << device->getCurrentBitDepth() << std::endl;
            std::cout << "  Sample rate    : " << device->getCurrentSampleRate() << std::endl;
            this->bitDepth = device->getCurrentBitDepth();
            this->sampleRate = device->getCurrentSampleRate();
        }

        void audioDeviceIOCallbackWithContext(const float *const *inputChannelData,
                                              int numInputChannels,
                                              float *const *outputChannelData,
                                              int numOutputChannels,
                                              int numSamples,
                                              const juce::AudioIODeviceCallbackContext &context) override {
            juce::AudioBuffer<float> buffer(outputChannelData, numOutputChannels, numSamples);
            float value = 0;
            for (int i = 0; i < numSamples; i++) {
                value = this->gain * ((float) rand() / (float) RAND_MAX);
                buffer.setSample(0, i, value);
                //buffer.setSample(1, i, value);
            }
            count++;
            auto now = juce::Time::getCurrentTime();
            if (now.toMilliseconds() - this->checkpoint.toMilliseconds() > 1000) {
                std::cout << this->myDeviceName << " CHECKPOINT" << std::endl;
                std::cout << "  input channels : " << numInputChannels << std::endl;
                std::cout << "  output channels: " << numOutputChannels << "; sample count: " << numSamples
                          << std::endl;
                std::cout << "  last sample    : " << value << std::endl;
                count = 0;
                this->checkpoint = now;
            }
        }

        void audioDeviceStopped() override {
            std::cout << "Device stopped!";
        }

    };

#ifndef AUDIO_BLOCK_SAMPLES
#define AUDIO_BLOCK_SAMPLES 128
#endif // AUDIO_BLOCK_SAMPLES

    typedef struct audio_block_struct {
        uint8_t ref_count;
        uint8_t reserved1;
        uint16_t memory_pool_index;
        int16_t data[AUDIO_BLOCK_SAMPLES];
    } audio_block_t;

    class AudioStream {

    public:
        AudioStream(unsigned char ninput, audio_block_t **iqueue) {}

    protected:
        static audio_block_t *allocate(void);

        static void release(audio_block_t *block);

        void transmit(audio_block_t *block, unsigned char index = 0);

    private:
        virtual void update(void) = 0;

    };

    void AudioStream::transmit(audio_block_t *block, unsigned char index) {}

    void AudioStream::release(audio_block_t *block) {}

    audio_block_t *AudioStream::allocate(void) { return nullptr; }
} // namespce thingy
#endif // THINGY_AUDIO_H
#else // ARDUINO
#include <Arduino.h>
#include <Audio.h>
#endif // TARGET_NATIVE