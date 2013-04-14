/*
 Copyright 2012 PettyFun Limited.  All rights reserved.
 */

#include "PfAudio.h"

void PfAudioInit(bool useLibBass) {
    PfAudioUtils::Create();
    PF_AUDIO_UTILS->Init();
    
    PfAudio::Create();
    PF_AUDIO->Init(useLibBass);
}

void PfAudioTerminate() {
    PF_AUDIO->Release();
    PfAudio::Destroy();
    
    PF_AUDIO_UTILS->Release();
    PfAudioUtils::Destroy();
}

CDECLARE_SINGLETON(PfAudio)

void PfAudio::Init(bool useLibBass) {
    UseLibBass = useLibBass;
    Available = false;
    
    if (!useLibBass) {
        PfAudio_ReleaseInfo("PfAudio: NOT using libBass");
    } else if (s3eBassAvailable()) {
        Available = s3eBASS_Init(-1, 44100, 0, 0, NULL);
        if (!Available) {
            PfAudio_ReleaseInfo("PfAudio: Failed to Init Bass");
        } else {
            s3eBASS_Start();
            PfAudio_ReleaseInfo("PfAudio: Bass Started");
        }
    } else {
        PfAudio_ReleaseInfo("PfAudio: s3eBass is not available");
    }
}

void PfAudio::Release() {
    if (Available) {
        Samples.ClearAndFree();
        Streams.ClearAndFree();
        Musics.ClearAndFree();
        s3eBASS_Stop();
        s3eBASS_Free();
    }
}

const char* PfAudio::GetAudioPath(const char* folder, Json::Value settings) {
    Json::Value filename = settings["filename"];
    if (filename.empty()) {
        return NULL;
    }
    return PF_AUDIO_UTILS->GetRealPath(folder, filename.asCString());
}

const char* PfAudio::GetAudioKey(const char* folder, Json::Value settings) {
    Json::Value name = settings["name"];
    char* key = new char[PF_AUDIO_File_Path_Buffer_Size];
    if (name.empty()) {
        Json::Value filename = settings["filename"];
        snprintf(key, PF_AUDIO_File_Path_Buffer_Size, "%s/%s", folder, filename.asCString());
    } else {
        snprintf(key, PF_AUDIO_File_Path_Buffer_Size, "%s/%s", folder, name.asCString());
    }
    return key;
}

PfSample* PfAudio::CreateSample(const char* folder, Json::Value settings) {
    const char* path = GetAudioPath(folder, settings);
    if (path == NULL) return NULL;
    PfSample* result = NULL;
    //PfAudio_ReleaseTrace("PfAudio: PfAudio::CreateSample: try loading sample: %s", path);
    
    DWORD offset = settings.get("offset", PF_SAMPLE_DEFAULT_OFFSET).asInt();
    DWORD length = settings.get("length", PF_SAMPLE_DEFAULT_LENGTH).asInt();
    DWORD max = settings.get("max", PF_SAMPLE_DEFAULT_MAX).asInt();
    DWORD flags = settings.get("flags", PF_SAMPLE_DEFAULT_FLAGS).asInt();
    HSAMPLE sample = s3eBASS_SampleLoad(false, path, offset, length, max, flags);
    if (sample == PF_AUDIO_BASS_NULL) {
        PfAudio_ReleaseTrace("PfAudio: PfAudio::CreateSample: Error loading sample: %s, %d", path, s3eBASS_ErrorGetCode());
    } else {
        result = new PfSample(sample, settings);
        const char* key = GetAudioKey(folder, settings);
        result->SetName(key);
        //PfAudio_ReleaseTrace("PfAudio: PfAudio::CreateSample: sample added: %s, %s", key, path);
        delete [] key;
    }
    delete [] path;
    return result;
}

PfStream* PfAudio::CreateStream(const char* folder, Json::Value settings) {
    const char* path = GetAudioPath(folder, settings);
    if (path == NULL) return NULL;
    PfStream* result = NULL;
    //PfAudio_ReleaseTrace("PfAudio: PfAudio::CreateStream: try loading stream: %s", path);
    
    DWORD offset = settings.get("offset", PF_STREAM_DEFAULT_OFFSET).asInt();
    DWORD length = settings.get("length", PF_STREAM_DEFAULT_LENGTH).asInt();
    DWORD flags = settings.get("flags", PF_STREAM_DEFAULT_FLAGS).asInt();
    HSTREAM stream = s3eBASS_StreamCreateFile(false, path, offset, length, flags);
    if (stream == PF_AUDIO_BASS_NULL) {
        PfAudio_ReleaseTrace("PfAudio: PfAudio::CreateStream: Error loading stream: %s, %d", path, s3eBASS_ErrorGetCode());
    } else {
        result = new PfStream(stream, settings);
        const char* key = GetAudioKey(folder, settings);
        result->SetName(key);
        //PfAudio_ReleaseTrace("PfAudio: PfAudio::CreateStream: stream added: %s, %s", key, path);
        delete [] key;
    }
    delete [] path;
    return result;
}

bool PfAudio::LoadFolder(const char* folder, Audio_Types audioType) {
    if (!Available) return false;
    if (audioType == PA_Music) return false; //NOT IMPLEMENTED
    
    char relPath[PF_AUDIO_File_Path_Buffer_Size];
    switch (audioType) {
        case PA_Sample:
            snprintf(relPath, PF_AUDIO_File_Path_Buffer_Size, "%s/%s/%s", PF_AUDIO_UTILS->GetAudioFolder(), folder, PF_AUDIO_Samples_Filename);
            break;
        case PA_Stream:
            snprintf(relPath, PF_AUDIO_File_Path_Buffer_Size, "%s/%s/%s", PF_AUDIO_UTILS->GetAudioFolder(), folder, PF_AUDIO_Streams_Filename);
            break;
    }
    PfAudio_ReleaseTrace("PfAudio::LoadFolder() loading: %s", relPath);
    Json::Value* definition = PF_AUDIO_UTILS->ReadJson(relPath);
    PfAudio_ReleaseTrace("PfAudio::LoadFolder(): the definition file is %s", (definition == NULL) ? "NULL" : "OK");
    if (definition != NULL) {
        Json::Value defaultValue(Json::objectValue);
        for (unsigned int i = 0; i < definition->size(); i++) {
            switch (audioType) {
                case PA_Sample: {
                    PfSample* sample = CreateSample(folder, definition->get(i, defaultValue));
                    if (sample != NULL) {
                        PfSample* oldSample = (PfSample *)Samples.GetObjHashed(sample->m_Hash);
                        if (oldSample != NULL) {
                            Samples.RemoveFast(oldSample);
                            delete oldSample;
                        }
                        Samples.Add(sample);
                    }
                    break;
                }
                case PA_Stream: {
                    PfStream* stream = CreateStream(folder, definition->get(i, defaultValue));
                    if (stream != NULL) {
                        PfStream* oldStream = (PfStream *)Streams.GetObjHashed(stream->m_Hash);
                        if (oldStream != NULL) {
                            Streams.RemoveFast(oldStream);
                            delete oldStream;
                        }
                        Streams.Add(stream);
                    }
                    break;
                }
            }
        }
        delete definition;
        return true;
    }
    return false;
}

bool PfAudio::UnloadSamples(const char* folder) {
    if (!Available) return false;

    //TODO
    return false;
}

PfSampleChannel* PfAudio::GetFreeSampleChannel(const char* key) {
    if (!Available) return NULL;

    PfSampleChannel* result = NULL;
    PfSample* sample = (PfSample *)Samples.GetObjNamed(key);
    if (sample != NULL) {
        result = sample->GetFreeChannel();
    }
    return result;
}

PfSampleChannel* PfAudio::PlaySample(const char* key, float volume, float pitch, float pan) {
    if (!Available) return NULL;

    PfSampleChannel* result = GetFreeSampleChannel(key);
    if (result != NULL) {
        result->SetVolume(volume);
        result->SetPitch(pitch);
        result->SetPan(pan);
        result->Play();
    }
    return result;
}

bool PfAudio::UnloadStreams(const char* folder) {
    if (!Available) return false;
    
    //TODO
    return false;
}

PfStream* PfAudio::GetStream(const char* key) {
    PfStream* stream = (PfStream *)Streams.GetObjNamed(key);
    return stream;
}

PfStream* PfAudio::PlayStream(const char* key, float volume, bool loop, int fadeInTime) {
    if (!Available) return NULL;
    
    PfStream* result = GetStream(key);
    if (result != NULL) {
        result->SetVolume(volume);
        result->SetLoop(loop);
        if (!result->IsPlaying()) {
            result->Play(fadeInTime);            
        }
    }
    return result;
}

bool PfAudio::StopAllStreams() {
    IW_MANAGED_LIST_ITERATE(Streams, it) {
        PfStream* stream = (PfStream *)(*it);
        if (stream->IsPlaying()) {
            stream->Stop();
        }
    }
    return true;
}

