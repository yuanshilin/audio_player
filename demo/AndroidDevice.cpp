//
// Created by frank on 2021/8/30.
//

#include "AndroidDevice.h"



AndroidDevice::AndroidDevice(uint32_t numChannels, uint32_t sampleRate, uint32_t frameSize)
    : AudioDevice(numChannels, sampleRate, frameSize)
{}

int AndroidDevice::Play(const std::vector<float> &data) {
    printf("android device play\n");
    return 0;
}