//
// Created by Orion Letizi on 2/25/23.
//

#ifndef THINGY_THINGY_AUDIO_H
#define THINGY_THINGY_AUDIO_H

#ifdef TARGET_NATIVE
class MyAudioCallback : public juce::AudioIODeviceCallback {
    std::string myDeviceName;
    juce::Time checkpoint = juce::Time::getCurrentTime();
    int count = 0;
    int bitDepth = 0;
    double sampleRate = 0;
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
        count++;
        auto now = juce::Time::getCurrentTime();
        if (now.toMilliseconds() - this->checkpoint.toMilliseconds() > 5000) {
            std::cout << this->myDeviceName << " CHECKPOINT" << std::endl;
            std::cout << "  input channels: " << numInputChannels << std::endl;
            std::cout << "  output channels: " << numOutputChannels << "; sample count: " << numSamples << std::endl;
            count = 0;
            this->checkpoint = now;
        }
    }

    void audioDeviceStopped() override {
        std::__1::cout << "Device stopped!";
    }

};

#else // ARDUINO

#endif // TARGET_NATIVE

#endif //THINGY_THINGY_AUDIO_H
