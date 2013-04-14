/*
 Copyright 2012 PettyFun Limited.  All rights reserved.
 */

#ifndef _PFAUDIO_H_
#define _PFAUDIO_H_

#include "stddef.h"
#include "IwDebug.h"
#include "s3eBass.h"
#include "IwManagedList.h"

#include "PfAudioUtils.h"
#include "PfSample.h"
#include "PfStream.h"
#include "PfMusic.h"

#define	PF_AUDIO (PfAudio::getInstance())

void PfAudioInit(bool useLibBass);
void PfAudioTerminate();

class PfAudio {
private:
    enum Audio_Types
	{
        PA_Sample,
        PA_Stream,
        PA_Music
	};
    bool UseLibBass;
    bool Available;
    CIwManagedList Samples;
    CIwManagedList Streams;
    CIwManagedList Musics;
    const char* GetAudioPath(const char* folder, Json::Value settings);
    const char* GetAudioKey(const char* folder, Json::Value settings);
    PfSample* CreateSample(const char* folder, Json::Value settings);
    PfStream* CreateStream(const char* folder, Json::Value settings);
    bool LoadFolder(const char* folder, Audio_Types audioType);
public:
    CDEFINE_SINGLETON(PfAudio)
    void Init(bool useLibBass);
    void Release();
    bool IsAvailable() {
        return Available;
    }
    
    bool LoadSamples(const char* folder) {
        return LoadFolder(folder, PA_Sample);
    }
    bool UnloadSamples(const char* folder);
    PfSampleChannel* GetFreeSampleChannel(const char* key);
    PfSampleChannel* PlaySample(const char* key, float volume=1.0f, float pitch=1.0f, float pan=0.0f);

    bool LoadStreams(const char* folder) {
        return LoadFolder(folder, PA_Stream);
    }
    bool UnloadStreams(const char* folder);
    PfStream* GetStream(const char* key);
    PfStream* PlayStream(const char* key, float volume=1.0f, bool loop=false, int fadeInTime=0);
    bool StopAllStreams();
};

#endif// _PFAUDIO_H_
