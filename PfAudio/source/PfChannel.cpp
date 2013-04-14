/*
 Copyright 2012 PettyFun Limited.  All rights reserved.
 */

#include "PfChannel.h"

IW_MANAGED_IMPLEMENT(PfChannel);

bool PfChannel::SetVolume(float volume) {
    //For some reason, if set to 1.0f, for mp3 files, there is no sound.
    if (volume > 0.99f) volume = 0.99f;
    if (volume < 0.0f) volume = 0.0f;
    return s3eBASS_ChannelSetAttribute(Channel, BASS_ATTRIB_VOL, volume);
}

bool PfChannel::SetPan(float pan) {
    return s3eBASS_ChannelSetAttribute(Channel, BASS_ATTRIB_PAN, pan);
}

bool PfChannel::SetLoop(bool loop) {
    if (loop) {
        int result = s3eBASS_ChannelFlags(Channel, BASS_SAMPLE_LOOP, BASS_SAMPLE_LOOP);
        if (result == -1) return false;
        return result & BASS_SAMPLE_LOOP != 0;
    } else {
        int result = s3eBASS_ChannelFlags(Channel, 0, BASS_SAMPLE_LOOP);
        if (result == -1) return false;
        return result & BASS_SAMPLE_LOOP == 0;
    }
}

bool PfChannel::Play(int fadeInTime, bool restart) {
    //TODO: fade in not working yet, just no sound output
    if (false && fadeInTime > 0) {
        float volume;
        if (!s3eBASS_ChannelGetAttribute(Channel, BASS_ATTRIB_VOL, &volume)) return false;
        if (!s3eBASS_ChannelSetAttribute(Channel, BASS_ATTRIB_VOL, 0)) return false;
        if (!s3eBASS_ChannelSlideAttribute(Channel, BASS_ATTRIB_VOL, volume, fadeInTime)) return false;
    }
    return s3eBASS_ChannelPlay(Channel, restart);
}

bool PfChannel::Stop(int fadeOutTime) {
    //TODO: fade out not working yet, just got cut immediately
    if (false && fadeOutTime > 0) {
        // negative value means the channel will be stopped after slide done.
        // http://www.un4seen.com/doc/#bass/BASS_ATTRIB_VOL.html
        return s3eBASS_ChannelSlideAttribute(Channel, BASS_ATTRIB_VOL, -0.1f, fadeOutTime);
    } else {
        return s3eBASS_ChannelStop(Channel);
    }
}

bool PfChannel::Pause() {
    return s3eBASS_ChannelPause(Channel);
}

bool PfChannel::Resume() {
    return s3eBASS_ChannelPlay(Channel, false);
}

bool PfChannel::IsPlaying() {
    DWORD result = s3eBASS_ChannelIsActive(Channel);
    return result == BASS_ACTIVE_PLAYING;
}
