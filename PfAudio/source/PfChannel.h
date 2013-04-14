/*
 Copyright 2012 PettyFun Limited.  All rights reserved.
 */

#ifndef _PFCHANNEL_H_
#define _PFCHANNEL_H_

#include "s3eBass.h"
#include "IwManaged.h"
#include "IwList.h"
#include "PfAudioUtils.h"

class PfChannel : public CIwManaged {
protected:
    HCHANNEL Channel;
public:
    IW_MANAGED_DECLARE(PfChannel);
    PfChannel(HCHANNEL channel): Channel(NULL) {
        Channel = channel;
    }
    HCHANNEL GetChannel() {
        return Channel;
    }
    bool SetVolume(float volume);
    bool SetPan(float pan);
    bool SetLoop(bool loop);
    bool Play(int fadeInTime=0, bool restart=false);
    bool Stop(int fadeOutTime=0);
    bool Pause();
    bool Resume();
    bool IsPlaying();
};



#endif// _PFCHANNEL_H_
