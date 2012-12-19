// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2006 RobotCub Consortium
 * Authors: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */


#include <yarp/os/impl/Carriers.h>
#include <yarp/os/impl/Logger.h>
#include <yarp/os/impl/TcpFace.h>
#include <yarp/os/impl/FakeFace.h>
#include <yarp/os/impl/TcpCarrier.h>
#include <yarp/os/impl/TextCarrier.h>

#ifdef YARP_HAS_ACE
#  include <yarp/os/impl/UdpCarrier.h>
#  include <yarp/os/impl/McastCarrier.h>
#  include <yarp/os/impl/ShmemCarrier.h>
#endif

#include <yarp/os/impl/LocalCarrier.h>
#include <yarp/os/impl/NameserCarrier.h>
#include <yarp/os/impl/HttpCarrier.h>
#include <yarp/os/impl/Logger.h>
#include <yarp/os/impl/PlatformStdlib.h>

using namespace yarp::os::impl;
using namespace yarp::os;

static Logger carriersLog("Carriers", Logger::get());

Carriers *Carriers::yarp_carriers_instance = NULL;

static bool matchCarrier(const Bytes *header, Bottle& code) {
    int at = 0;
    bool success = true;
    bool done = false;
    for (int i=0; i<code.size() && !done; i++) {
        Value& v = code.get(i);
        if (v.isString()) {
            ConstString str = v.asString();
            for (int j=0; j<(int)str.length(); j++) {
                if ((int)header->length()<=at) {
                    success = false;
                    done = true;
                    break;
                }
                if (str[j] != header->get()[at]) {
                    success = false;
                    done = true;
                    break;
                }
                at++;
            }
        } else {
            at++;
        }
    }
    return success;
}

static bool checkForCarrier(const Bytes *header, const char *fname) {
    Property config;
    config.fromConfigFile(fname);
    Bottle plugins = config.findGroup("plugin").tail();
    for (int i=0; i<plugins.size(); i++) {
        ConstString name = plugins.get(i).asString();
        Bottle group = config.findGroup(name);
        Bottle code = group.findGroup("code").tail();
        if (matchCarrier(header,code)) {
            ConstString dll_name = group.find("library").asString();
            ConstString fn_name = group.find("part").asString();
            if (NetworkBase::registerCarrier(fn_name.c_str(),
                                             dll_name.c_str())) {
                return true;
            }
        }
    }
    return false;
}

static bool scanForCarrier(const Bytes *header) {
    bool success = false;
    ConstString dirname = "/etc/yarp/carriers";
    ACE_DIR *dir = ACE_OS::opendir(dirname.c_str());
    if (!dir) {
        YARP_SPRINTF0(Logger::get(),debug,"Could not find /etc/yarp/carriers");
        return false;
    }
    struct ACE_DIRENT *ent = ACE_OS::readdir(dir);
    while (ent) {
        ConstString name = ent->d_name;
        ent = ACE_OS::readdir(dir);
        int len = (int)name.length();
        if (len<4) continue;
        if (name.substr(len-4)!=".ini") continue;
        if (checkForCarrier(header,(dirname + "/" + name).c_str())) {
            success = true;
            break;
        }
    }
    ACE_OS::closedir(dir);
    dir = NULL;
    return success;
}

Carriers::Carriers() {
    delegates.push_back(new HttpCarrier());
    delegates.push_back(new NameserCarrier());
    delegates.push_back(new LocalCarrier());
#ifdef YARP_HAS_ACE
    //delegates.push_back(new ShmemCarrier(1));
    delegates.push_back(new ShmemCarrier(2)); // new Alessandro version
#endif
    delegates.push_back(new TcpCarrier());
    delegates.push_back(new TcpCarrier(false));
#ifdef YARP_HAS_ACE
    delegates.push_back(new McastCarrier());
    delegates.push_back(new UdpCarrier());
#endif
    delegates.push_back(new TextCarrier());
    delegates.push_back(new TextCarrier(true));
}

Carriers::~Carriers() {
    clear();
}

void Carriers::clear() {
    PlatformVector<Carrier *>& lst = delegates;
    for (unsigned int i=0; i<lst.size(); i++) {
        delete lst[i];
    }
    lst.clear();
}

Carrier *Carriers::chooseCarrier(const String *name, const Bytes *header,
                                 bool load_if_needed) {
    String s;
    if (name!=NULL) {
        s = *name;
        YARP_STRING_INDEX i = YARP_STRSTR(s,"+");
        if (i!=String::npos) {
            s[i] = '\0';
            s = s.c_str();
            name = &s;
        }
    }
    for (YARP_STRING_INDEX i=0; i<(YARP_STRING_INDEX)delegates.size(); i++) {
        Carrier& c = *delegates[i];
        bool match = false;
        if (name!=NULL) {
            if ((*name) == c.getName()) {
                match = true;
            }
        }
        if (header!=NULL) {
            if (c.checkHeader(*header)) {
                match = true;
            }
        }
        if (match) {
            return c.create();
        }
    }
    if (load_if_needed) {
        if (name!=NULL) {
            // ok, we didn't find a carrier, but we have a name.
            // let's try to register it, and see if a dll is found.
            if (NetworkBase::registerCarrier(name->c_str(),NULL)) {
                // We made progress, let's try again...
                return Carriers::chooseCarrier(name,header,false);
            }
        } else {
            if (scanForCarrier(header)) {
                // We made progress, let's try again...
                return Carriers::chooseCarrier(name,header,true);
            }
        }
    }
    YARP_SPRINTF1(Logger::get(),
                  error,
                  "Could not find carrier \"%s\"", 
                  (name!=NULL)?name->c_str():"[bytes]");;
    //throw IOException("Could not find carrier");
    return NULL;
}


Carrier *Carriers::chooseCarrier(const String& name) {
    return getInstance().chooseCarrier(&name,NULL);
}

Carrier *Carriers::chooseCarrier(const Bytes& bytes) {
    return getInstance().chooseCarrier(NULL,&bytes);
}


Face *Carriers::listen(const Address& address) {
    // for now, only TcpFace exists - otherwise would need to manage 
    // multiple possibilities
    //YARP_DEBUG(carriersLog,"listen called");
    Face *face = NULL;
    if (address.getCarrierName() == String("fake")) {
        face = new FakeFace();
    }
    if (face == NULL) {
        face = new TcpFace();
    }
    bool ok = face->open(address);
    if (!ok) {
        delete face;
        face = NULL;
    }
    return face;
}


OutputProtocol *Carriers::connect(const Address& address) {
    TcpFace tcpFace;
    return tcpFace.write(address);
}


bool Carriers::addCarrierPrototype(Carrier *carrier) {
    getInstance().delegates.push_back(carrier);
    return true;
}


bool Carrier::reply(Protocol& proto, SizedWriter& writer) {
    return proto.defaultReply(writer);
}

Carriers& Carriers::getInstance() {
    if (yarp_carriers_instance == NULL) {
        yarp_carriers_instance = new Carriers();
        YARP_ASSERT(yarp_carriers_instance!=NULL);
    }
    return *yarp_carriers_instance;
}


void Carriers::removeInstance() {
    if (yarp_carriers_instance != NULL) {
        delete yarp_carriers_instance;
        yarp_carriers_instance = NULL;
    }
}
