// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2006 Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <ace/config.h>
#include <ace/OS_NS_string.h>

#include <yarp/os/ManagedBytes.h>

using namespace yarp::os;

void ManagedBytes::copy() {
    if (!owned) {
        int len = length();
        char *buf = new char[len];
        yarp::os::NetworkBase::assertion(buf!=NULL);
        ACE_OS::memcpy(buf,get(),len);
        b = Bytes(buf,len);
        owned = true;
    }
}
