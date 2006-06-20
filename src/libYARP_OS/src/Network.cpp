// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-
#include <ace/ACE.h>


#include <yarp/os/Network.h>
#include <yarp/os/Time.h>

#include <yarp/Companion.h>
#include <yarp/NameClient.h>
#include <yarp/NameConfig.h>
#include <yarp/Logger.h>
#include <yarp/os/Bottle.h>

using namespace yarp;
using namespace yarp::os;

bool Network::connect(const char *src, const char *dest, bool quiet) {
    int result = Companion::connect(src,dest,quiet);
    return result == 0;
}


bool Network::disconnect(const char *src, const char *dest, bool quiet) {
    int result = Companion::disconnect(src,dest,quiet);
    return result == 0;
}


int Network::main(int argc, char *argv[]) {
    return Companion::main(argc,argv);
}


void Network::init() {
    ACE::init();
    String verbose = NameConfig::getEnv("YARP_VERBOSE");
    Bottle b(verbose.c_str());
    if (b.get(0).asInt()>0) {
        YARP_INFO(Logger::get(), "YARP_VERBOSE environment variable is set");
        Logger::get().setVerbosity(b.get(0).asInt());
    }
	// make sure system is actually able to do things fast
	Time::turboBoost();
}

void Network::fini() {
    ACE::fini();
}

Contact Network::queryName(const char *name) {
    NameClient& nic = NameClient::getNameClient();
    Address address = nic.queryName(name);
    return address.toContact();
}


Contact Network::registerName(const char *name) {
    NameClient& nic = NameClient::getNameClient();
    Address address = nic.registerName(name);
    return address.toContact();
}


Contact Network::registerContact(const Contact& contact) {
    NameClient& nic = NameClient::getNameClient();
    Address address = nic.registerName(contact.getName().c_str(),
                                       Address::fromContact(contact));
    return address.toContact();
}

Contact Network::unregisterName(const char *name) {
    NameClient& nic = NameClient::getNameClient();
    Address address = nic.unregisterName(name);
    return address.toContact();
}


Contact Network::unregisterContact(const Contact& contact) {
    NameClient& nic = NameClient::getNameClient();
    Address address = nic.unregisterName(contact.getName().c_str());
    return address.toContact();
}

bool Network::setLocalMode(bool flag) {
    NameClient& nic = NameClient::getNameClient();
    bool state = nic.isFakeMode();
    nic.setFakeMode(flag);
    return state;
}

