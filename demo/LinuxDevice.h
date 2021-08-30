//
// Created by frank on 2021/8/30.
//

#ifndef WAV_LINUXDEVICE_H
#define WAV_LINUXDEVICE_H

#include <cstdint>
#include "AudioDevice.h"

class LinuxDevice : public AudioDevice {
public:
    LinuxDevice(uint32_t numChannels, uint32_t sampleRate, uint32_t frameSize);
    virtual int Play(const std::vector<float> &data) override;
};


#endif //WAV_LINUXDEVICE_H
