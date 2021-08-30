//
// Created by frank on 2021/8/30.
//

#include <vector>
#include "LinuxDevice.h"


int LinuxDevice::Play(const std::vector<float> &data) {
    printf("linux device play\n");
    return 0;
}

LinuxDevice::LinuxDevice(uint32_t numChannels, uint32_t sampleRate, uint32_t frameSize)
: AudioDevice(numChannels,sampleRate, frameSize)
{

}
