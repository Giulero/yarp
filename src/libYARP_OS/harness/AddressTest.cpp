// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2006 Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <yarp/os/impl/Address.h>
#include <yarp/os/Contact.h>

#include <yarp/os/impl/UnitTest.h>
//#include "TestList.h"

using namespace yarp::os::impl;
using namespace yarp::os;

class AddressTest : public UnitTest {
public:
    virtual String getName() { return "AddressTest"; }

    virtual void testString() {
        report(0,"checking string representation");
        Address address("127.0.0.1",10000,"tcp");
        String txt = address.toString();
        checkEqual(txt,"tcp://127.0.0.1:10000","string rep example");
    }

    virtual void testCopy() {
        report(0,"checking address copy");
        Address address("127.0.0.1",10000,"tcp");
        Address address2;
        address2 = address;
        String txt = address2.toString();
        checkEqual(txt,"tcp://127.0.0.1:10000","string rep example");

        Address inv1;
        address2 = inv1;
        checkTrue(!inv1.isValid(),"invalid source");
        checkTrue(!address2.isValid(),"invalid copy");
    }

    virtual void testContact() {
        report(0,"checking Contact wrapper");
        Contact c1;
        Address inv1;
        c1 = inv1.toContact();
        checkTrue(!Contact::invalid().isValid(),"good invalid");
        checkTrue(!inv1.isValid(),"invalid source");
        checkTrue(!inv1.toContact().isValid(),"invalid conversion");
        checkTrue(!c1.isValid(),"invalid copy");
    }

    virtual void runTests() {
        testString();
        testCopy();
        testContact();
    }
};

static AddressTest theAddressTest;

UnitTest& getAddressTest() {
    return theAddressTest;
}

