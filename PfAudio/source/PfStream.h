/*
 Copyright 2012 PettyFun Limited.  All rights reserved.
 */

#ifndef _PFSTREAM_H_
#define _PFSTREAM_H_

#include "PfChannel.h"

#define PF_STREAM_DEFAULT_OFFSET 0
#define PF_STREAM_DEFAULT_LENGTH 0
#define PF_STREAM_DEFAULT_FLAGS 0

class PfStream : public PfChannel {
protected:
    HSTREAM Stream;
public:
    PfStream(HSTREAM stream, Json::Value settings): PfChannel(stream) {
        Stream = stream;
    }
};

#endif// _PFSTREAM_H_
