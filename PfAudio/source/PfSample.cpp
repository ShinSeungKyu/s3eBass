/*
 Copyright 2012 PettyFun Limited.  All rights reserved.
 */

#include "PfSample.h"

IW_MANAGED_IMPLEMENT(PfSample);

PfSampleChannel* PfSample::GetFreeChannel(bool onlyNew) {
    PfSampleChannel* result = NULL;
    HCHANNEL bassChannel = s3eBASS_SampleGetChannel(Sample, onlyNew);
    if (bassChannel == PF_AUDIO_BASS_NULL) return result;

    for (CIwList<PfSampleChannel*>::iterator it = Channels.begin(); it != Channels.end(); ++it) {
        PfSampleChannel* channel = *it;
        if (channel->GetChannel() == bassChannel) {
            result = channel;
            break;
        }
    }
    if (result == NULL) {
        result = new PfSampleChannel(this, bassChannel);
        Channels.append(result);
    }
    return result;
}

bool PfSampleChannel::SetPitch(float pitch) {
    return s3eBASS_ChannelSetAttribute(Channel, BASS_ATTRIB_FREQ, pitch * Sample->GetInfo().freq);
}

