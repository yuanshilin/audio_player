// Note to Visual Studio / Windows users: you must set the working directory manually on the project file
// to $(ProjectDir)../ since these settings are not saved directly in project. The loader
// will be unable to find the example assets unless the proper working directory is set.

#if defined(_MSC_VER)
#pragma comment(lib, "dsound.lib")
#endif

#include "AudioDevice.h"
#include "Decoders.h"
//#include "Encoders.h"

#if ANDROID
#include "AndroidDevice.h"
#else
#include "LinuxDevice.h"
#endif

#include <thread>

using namespace nqr;




template<typename ... Args>
static std::string formatString(const std::string &format, Args ... args)
{
    auto size = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}


int main(int argc, const char **argv) try {


    std::string file;

    NyquistIO loader;

    if (argc > 1) {
        std::string cli_arg = std::string(argv[1]);
        file = cli_arg;
//        loader.Load(fileData.get(), cli_arg);
    } else {
#if  ANDROID
       file = std::string("/sdcard/7.1.wav");
#else
       file = std::string("/home/frank/mediafile/7.1.wav");
#endif
    }


    std::shared_ptr<AudioData> fileData = std::make_shared<AudioData>();

    loader.Load(fileData.get(), file);

    const int desiredSampleRate = fileData->sampleRate;
    const int desiredChannelCount = fileData->channelCount;
    const int frameSize = fileData->frameSize;

    printf("file:%s sampleRate:%d channel:%d  frameSize:%d\n",
            file.c_str(),desiredSampleRate, desiredChannelCount, frameSize);

    AudioDevice* pDevice = nullptr;
#if ANDROID
    pDevice = new AndroidDevice(desiredChannelCount, desiredSampleRate,0);
#else
    pDevice = new LinuxDevice(desiredChannelCount, desiredSampleRate,frameSize);
#endif //标志结束#if


    /* Test Recording Capabilities of AudioDevice
    fileData->samples.reserve(44100 * 5);
    fileData->channelCount = 1;
    fileData->frameSize = 32;
    fileData->lengthSeconds = 5.0;
    fileData->sampleRate = 44100;
    std::cout << "Starting recording ..." << std::endl;
    myDevice.Record(fileData->sampleRate * fileData->lengthSeconds, fileData->samples);
    */

    std::cout << "Input Samples: " << fileData->samples.size() << std::endl;

    // Convert mono to stereo for testing playback
    if (fileData->channelCount == 1) {
        std::cout << "Playing MONO for: " << fileData->lengthSeconds << " seconds..." << std::endl;
        std::vector<float> stereoCopy(fileData->samples.size() * 2);
        MonoToStereo(fileData->samples.data(), stereoCopy.data(), fileData->samples.size());
        pDevice->Play(stereoCopy);
    } else if (fileData->channelCount == 2) {
        std::cout << "Playing STEREO for: " << fileData->lengthSeconds << " seconds..." << std::endl;
        pDevice->Play(fileData->samples);
    } else if (fileData->channelCount == 6) {
        std::cout << "Playing 5.1 for: " << fileData->lengthSeconds << " seconds..." << std::endl;
        pDevice->Play(fileData->samples);
    } else {
        std::cout << "Playing 7.1 for: " << fileData->lengthSeconds << " seconds..." << std::endl;
        pDevice->Play(fileData->samples);
    }

    std::string pcmFile = formatString("/home/frank/mediafile/audio_ch%d_rate%d_frame%d.pcm",
                                         fileData->channelCount, fileData->sampleRate, fileData->frameSize);


    FILE* pFile = fopen(pcmFile.c_str(),"wb+");
    if(nullptr == pFile) {
        printf("open file:%s failed\n", pcmFile.c_str());
        return -1;
    }

    printf("samples size:%d\n", fileData->samples.size());

    auto ret = fwrite( &fileData->samples[0], 1 , fileData->samples.size()* sizeof(float ) , pFile );
    if(ret < 0 ) {
        printf("write file:%s failed\n",pcmFile.c_str());
        return -1;
    }

    return EXIT_SUCCESS;
}
catch (const UnsupportedExtensionEx &e) {
    std::cerr << "Caught: " << e.what() << std::endl;
}
catch (const LoadPathNotImplEx &e) {
    std::cerr << "Caught: " << e.what() << std::endl;
}
catch (const LoadBufferNotImplEx &e) {
    std::cerr << "Caught: " << e.what() << std::endl;
}
catch (const std::exception &e) {
    std::cerr << "Caught: " << e.what() << std::endl;
}




