//
// Created by frank on 2021/8/30.
//

#ifndef WAV_ANDROIDDEVICE_H
#define WAV_ANDROIDDEVICE_H

#include "AudioDevice.h"

class AndroidDevice : public AudioDevice {
public:
    AndroidDevice(uint32_t numChannels, uint32_t sampleRate, uint32_t frameSize);
    virtual int Play(const std::vector<float> &data) override;
};


#endif //WAV_ANDROIDDEVICE_H
