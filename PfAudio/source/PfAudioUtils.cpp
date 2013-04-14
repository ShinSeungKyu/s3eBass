/*
 Copyright 2012 PettyFun Limited.  All rights reserved.
 */

#include "PfAudioUtils.h"

void PfAudio_doLogInRelease(const char* format, ...) {
    va_list argList;
    char debugText[1024] = {0};
    va_start(argList, format);
    vsnprintf(debugText, 1024, format, argList);
    va_end(argList);
    
    s3eDebugOutputString(debugText);
}

CDECLARE_SINGLETON(PfAudioUtils);

Json::Value* PfAudioUtils::ReadJson(const char* relPath) {
    Json::Value* result = NULL;
    
    s3eFile* file = s3eFileOpen(relPath, "r");
    
    if (file == NULL) {
        PfAudio_ReleaseTrace("PfAudio: Failed to open file: %s -> %s", relPath, s3eFileGetErrorString());
        return result;
    }
    
    char content[PF_AUDIO_File_Content_Buffer_Size];
    s3eFileRead(content, PF_AUDIO_File_Content_Buffer_Size, 1, file);

    Json::Reader reader;
    result = new Json::Value();
    bool parsingSuccessful = reader.parse(content, content + strlen(content), *result);
    if (!parsingSuccessful) {
        PfAudio_ReleaseTrace("PfAudio: PfAudioUtils::ReadJson(): Failed to parse json: %s\n%s", relPath, reader.getFormattedErrorMessages().c_str());
        delete result;
        result = NULL;
    }
    return result;
}

const char* PfAudioUtils::GetAudioFolder() {
    if (s3eDeviceGetInt(S3E_DEVICE_CLASS) == S3E_DEVICE_CLASS_WINDOWS_GENERIC) {
        return PF_AUDIO_Simulator_Folder;
    }
    return PF_AUDIO_Folder;
}

bool PfAudioUtils::CopyFile(const char* fromPath, const char* toPath) {
    s3eFile* fromFile = s3eFileOpen(fromPath, "rb");
    if (fromFile == NULL) {
        PfAudio_ReleaseTrace("PfAudio: PfAudioUtils::CopyFile(): Can't open to read: %s", fromPath);
        return false;
    }
    s3eFile* toFile = s3eFileOpen(toPath, "wb");
    if (toFile == NULL) {
        PfAudio_ReleaseTrace("PfAudio: PfAudioUtils::CopyFile(): Can't open to write: %s", toPath);
        s3eFileClose(fromFile);
        return false;
    }
    
    int fileSize = s3eFileGetSize(fromFile);
    uint8_t* buffer = new uint8_t[PF_AUDIO_File_Content_Buffer_Size];
    
    int readRounds = fileSize / PF_AUDIO_File_Content_Buffer_Size;
    int lastBufferSize = fileSize % PF_AUDIO_File_Content_Buffer_Size;
    if (lastBufferSize > 0) readRounds += 1;
    
    bool result = true;
    for (int i = 0; i < readRounds; i++) {
        int bufferSize = PF_AUDIO_File_Content_Buffer_Size;
        if (i == readRounds - 1 && lastBufferSize > 0) {
            bufferSize = lastBufferSize;
        }
        PfAudio_ReleaseTrace("PfAudio: PfAudioUtils::CopyFile(): %s - %s\nfileSize = %d, round = %d, bufferSize = %d", fromPath, toPath, fileSize, i, bufferSize);
        
        PfAudio_ReleaseInfo("PfAudio: PfAudioUtils::CopyFile(): READING");
        if (s3eFileRead(buffer, bufferSize, 1, fromFile) != 1) {
            PfAudio_ReleaseTrace("PfAudio: PfAudioUtils::CopyFile(): read failed: [%d - %s] %s", s3eFileGetError(), s3eFileGetErrorString(), fromPath);
            result = false;
            break;
        } else {
            PfAudio_ReleaseInfo("PfAudio: PfAudioUtils::CopyFile(): WRITING");
            if (s3eFileWrite(buffer, bufferSize, 1, toFile) != 1) {
            PfAudio_ReleaseTrace("PfAudio: PfAudioUtils::CopyFile(): write failed: [%d - %s] %s", s3eFileGetError(), s3eFileGetErrorString(), toPath);
            result = false;
            break;
            }
        }
        PfAudio_ReleaseInfo("PfAudio: PfAudioUtils::CopyFile(): ROUND DONE");
    }
    delete [] buffer;
    s3eFileClose(fromFile);
    s3eFileClose(toFile);
    if (!result) {
        s3eFileDelete(toPath);
    }
    return result;
}

char* PfAudioUtils::GetRelPath_Android(const char* folder, const char* file) {
    //On android, the audio files are under the assets folder in apk, not accessable by
    //libbass in this way, so copy them out first.
    char* ramPath = new char[PF_AUDIO_File_Path_Buffer_Size];
    snprintf(ramPath, PF_AUDIO_File_Path_Buffer_Size, "ram://%s/%s/%s", PF_AUDIO_Simulator_Folder, folder, file);
    
    s3eFile* ramFile = s3eFileOpen(ramPath, "rb");
    if (ramFile != NULL) {
        int fileSize = s3eFileGetSize(ramFile);
        s3eFileClose(ramFile);
        if (fileSize > 0) {
            return ramPath;
        } else {
            s3eFileDelete(ramPath);
        }
    }

    char folderPath[PF_AUDIO_File_Path_Buffer_Size];
    snprintf(folderPath, PF_AUDIO_File_Path_Buffer_Size, "ram://%s", PF_AUDIO_Simulator_Folder);
    s3eFileList* files = s3eFileListDirectory(folderPath);
    if (files != NULL) {
        s3eFileListClose(files);
    } else if (s3eFileMakeDirectory(folderPath) != S3E_RESULT_SUCCESS) {
        PfAudio_ReleaseTrace("PfAudio: PfAudioUtils::GetRelPath_Android(): Can't create directory: [%d - %s] %s", s3eFileGetError(), s3eFileGetErrorString(), folderPath);
        delete [] ramPath;
        return NULL;
    }
    snprintf(folderPath, PF_AUDIO_File_Path_Buffer_Size, "ram://%s/%s", PF_AUDIO_Simulator_Folder, folder);
    files = s3eFileListDirectory(folderPath);
    if (files != NULL) {
        s3eFileListClose(files);
    } else if (s3eFileMakeDirectory(folderPath) != S3E_RESULT_SUCCESS) {
        PfAudio_ReleaseTrace("PfAudio: PfAudioUtils::GetRelPath_Android(): Can't create directory: [%d - %s] %s", s3eFileGetError(), s3eFileGetErrorString(), folderPath);
        delete [] ramPath;
        return NULL;
    }

    char romPath[PF_AUDIO_File_Path_Buffer_Size];
    snprintf(romPath, PF_AUDIO_File_Path_Buffer_Size, "%s/%s/%s", PF_AUDIO_Folder, folder, file);

    if (s3eFileCheckExists(romPath) != S3E_TRUE) {
        PfAudio_ReleaseTrace("PfAudio: PfAudioUtils::GetRelPath_Android(): File not exist: %s", romPath);
        delete [] ramPath;
        return NULL;
    } else if (!CopyFile(romPath, ramPath)) {
        PfAudio_ReleaseTrace("PfAudio: PfAudioUtils::GetRelPath_Android(): Failed to copy file: %s -> %s", romPath, ramPath);
        delete [] ramPath;
        return NULL;
    }
    
    PfAudio_ReleaseTrace("PfAudio: PfAudioUtils::GetRelPath_Android(): result: %s", ramPath);
    return ramPath;
}

const char* PfAudioUtils::GetRealPath(const char* folder, const char* file) {
    char *relPath = NULL;
    if (s3eDeviceGetInt(S3E_DEVICE_OS) == S3E_OS_ID_ANDROID &&
        s3eDeviceGetInt(S3E_DEVICE_CLASS) != S3E_DEVICE_CLASS_WINDOWS_GENERIC) {
        relPath = GetRelPath_Android(folder, file);
        if (relPath == NULL) return NULL;
    } else {
        relPath = new char[PF_AUDIO_File_Path_Buffer_Size];
        snprintf(relPath, PF_AUDIO_File_Path_Buffer_Size, "%s/%s/%s", GetAudioFolder(), folder, file);
    }
    char* path = new char[PF_AUDIO_File_Path_Buffer_Size];
    if (s3eFileGetFileString(relPath, S3E_FILE_REAL_PATH, path, PF_AUDIO_File_Path_Buffer_Size) == NULL) {
        PfAudio_ReleaseTrace("PfAudio: PfAudioUtils::GetRealPath(): Failed to get full path: [%d] %s -> %s", s3eFileGetError(), s3eFileGetErrorString(), relPath);
        delete [] path;
        path = NULL;
    } else {
        snprintf(relPath, PF_AUDIO_File_Path_Buffer_Size, "raw://%s", path);
        if (s3eFileCheckExists(relPath) != S3E_TRUE) {
            PfAudio_ReleaseTrace("PfAudio: PfAudioUtils::GetRealPath(): File not exist: %s", path);
            delete [] path;
            path = NULL;
        }
    }
    delete [] relPath;
    return path;
}

