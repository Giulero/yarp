// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2006 Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#include <yarp/os/impl/BufferedConnectionWriter.h>
#include <yarp/os/impl/StreamConnectionReader.h>
#include <yarp/os/impl/NetType.h>
#include <yarp/os/impl/BufferedConnectionWriter.h>
#include <yarp/os/impl/Protocol.h>

#include <yarp/os/Bottle.h>

using namespace yarp::os::impl;
using namespace yarp::os;

yarp::os::ConnectionWriter *StreamConnectionReader::getWriter() {
    if (str==NULL) {
        return NULL;
    }
    if (writer==NULL) {
        writer = new BufferedConnectionWriter;
        YARP_ASSERT(writer!=NULL);
        writer->reset(isTextMode());
    }
    writer->clear();
    return writer;
}


void StreamConnectionReader::flushWriter() {
    if (writer!=NULL) {
        if (str!=NULL) {
            if (protocol!=NULL) {
                protocol->reply(*writer);
            } else {
                writer->write(str->getOutputStream());
            }
            writer->clear();
        }
    }
}


StreamConnectionReader::~StreamConnectionReader() {
    if (writer!=NULL) {
        delete writer;
        writer = NULL;
    }
}


bool StreamConnectionReader::convertTextMode() {
    Bottle bot;
    if (isTextMode()) {
        bot.read(*this);
        BufferedConnectionWriter writer;
        bot.write(writer);
        String s = writer.toString();
        altStream.reset(s);
        in = &altStream;
    }

    return true;
}


Bytes StreamConnectionReader::readEnvelope() {
    if (protocol==NULL) {
        return Bytes(0,0);
    }
    const String& env = protocol->getEnvelope();
    return Bytes((char*)env.c_str(),env.length());
}


