# Copyright (C) 2006-2021 Istituto Italiano di Tecnologia (IIT)
# All rights reserved.
#
# This software may be modified and distributed under the terms of the
# BSD-3-Clause license. See the accompanying LICENSE file for details.

if(NOT DEFINED CMAKE_MINIMUM_REQUIRED_VERSION)
  cmake_minimum_required(VERSION 3.12)
  project(threads)
  find_package(YARP REQUIRED COMPONENTS os)
endif()

add_executable(threads)
target_sources(threads PRIVATE threads.cpp)
target_link_libraries(threads PRIVATE YARP::YARP_os
                                      YARP::YARP_init)
set_property(TARGET threads PROPERTY FOLDER "Examples/os")
