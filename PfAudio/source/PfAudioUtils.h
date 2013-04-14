/*
 Copyright 2012 PettyFun Limited.  All rights reserved.
 */

#ifndef _PFAUDIOUTILS_H_
#define _PFAUDIOUTILS_H_

#include "json/json.h"
#include "s3eFile.h"
#include "IwDebug.h"

#define	PF_AUDIO_UTILS (PfAudioUtils::getInstance())

void PfAudio_doLogInRelease(const char* format, ...);

#define PfAudio_ReleaseInfo(info) PfAudio_doLogInRelease("[%s][%d] " info, __PfAudio_FILENAME__, __LINE__)
#define PfAudio_ReleaseInfoLine() PfAudio_ReleaseInfo("----------------------------------------------------------------------------------------------");
#define PfAudio_ReleaseTrace(format, ...) PfAudio_doLogInRelease("[%s][%d] " format, __PfAudio_FILENAME__, __LINE__, __VA_ARGS__)

#define __PfAudio_FILENAME__ \
(strrchr(__FILE__,'/') \
? strrchr(__FILE__,'/')+1 \
: __FILE__ \
)

#define PF_AUDIO_BASS_NULL 0

#define PF_AUDIO_Simulator_Folder "audio"
#define PF_AUDIO_Folder "rom://audio"
#define PF_AUDIO_Samples_Filename "Samples.json"
#define PF_AUDIO_Streams_Filename "Streams.json"
#define PF_AUDIO_File_Path_Buffer_Size 1024
#define PF_AUDIO_File_Content_Buffer_Size 102400

//
// Define a class as a singleton (Add to class definition in header file)
//
#define CDEFINE_SINGLETON(the_class)            \
private:                                        \
    static the_class* _instance;				\
    the_class() {}								\
    ~the_class() {}								\
    the_class(const the_class &);				\
    the_class& operator=(const the_class &);	\
public:											\
    static void Create();						\
    static void Destroy();						\
    static the_class* getInstance();

//
// Declare singleton methods (Add to source file)
//
#define CDECLARE_SINGLETON(the_class)		\
the_class* the_class::_instance = NULL;		\
void the_class::Create()					\
{											\
    if (_instance == NULL)					\
        _instance = new the_class;			\
}											\
void the_class::Destroy()					\
{											\
    if (_instance != NULL)					\
    {										\
        delete _instance;					\
        _instance = NULL;					\
    }										\
}											\
the_class* the_class::getInstance()			\
{											\
    return _instance;						\
}

class PfAudioUtils {
protected:
    char* GetRelPath_Android(const char* folder, const char* file);
public:
    CDEFINE_SINGLETON(PfAudioUtils);
    void Init() {}
    void Release() {}
    Json::Value* ReadJson(const char* relPath);
    const char* GetAudioFolder();
    const char* GetRealPath(const char* folder, const char* file);
    bool CopyFile(const char* fromPath, const char* toPath);
};


#endif// _PFAUDIOUTILS_H_
