/*
 * Copyright (C) 2006-2021 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef YARP_SEGFAULT_SEGFAULT_H
#define YARP_SEGFAULT_SEGFAULT_H

#include <yarp/os/Thread.h>
#include <yarp/dev/DeviceDriver.h>

/**
* @ingroup dev_impl_fake
*
* \brief `test_segfault`: A test device that causes a segmentation fault.
*/
class SegFault :
        public yarp::dev::DeviceDriver,
        public yarp::os::Thread
{
public:
    SegFault();
    SegFault(const SegFault&) = delete;
    SegFault(SegFault&&) = delete;
    SegFault& operator=(const SegFault&) = delete;
    SegFault& operator=(SegFault&&) = delete;

    ~SegFault() override;

    bool open(yarp::os::Searchable& config) override;
    bool close() override;

    void run() override;

private:
    yarp::conf::float64_t delay{1.0};
};

#endif // YARP_SEGFAULT_SEGFAULT_H
