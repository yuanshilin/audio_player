/*
Copyright (c) 2019, Dimitri Diakopoulos All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "AudioDevice.h"
#include <cmath>
#include <algorithm>
#include <thread>
#include <chrono>
#include <iostream>

static RingBufferT<float> buffer(BUFFER_LENGTH);

AudioDevice::AudioDevice(int numChannels, int sampleRate, int deviceId)
{
//    rtaudio = std::unique_ptr<RtAudio>(new RtAudio);
//    info.id = (deviceId != -1) ? deviceId : rtaudio->getDefaultOutputDevice();
    info.numChannels = numChannels;
    info.sampleRate = sampleRate;
    info.frameSize = FRAME_SIZE;
}

AudioDevice::~AudioDevice()
{

}


bool AudioDevice::Play(const std::vector<float> & data)
{

    // Each frame is the (size/2) cause interleaved channels!
//    int sizeInFrames = ((int) data.size()) / (BUFFER_LENGTH);
//
//    int writeCount = 0;
//
//    while (writeCount < sizeInFrames)
//    {
//        bool status = buffer.write((data.data() + (writeCount * BUFFER_LENGTH)), BUFFER_LENGTH);
//        if (status) writeCount++;
//    }
    return true;
}

