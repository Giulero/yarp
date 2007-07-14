// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2006 Lorenzo Natale, Giorgio Metta
 * CopyPolicy: Released under the terms of the GNU GPL v2.0.
 *
 */

#ifndef __YARPCONTROLBOARDINTERFACES__
#define __YARPCONTROLBOARDINTERFACES__

#include <yarp/dev/DeviceDriver.h>
#include <yarp/dev/ControlBoardPid.h>
#include <yarp/dev/CalibratorInterfaces.h>

/*! \file ControlBoardInterfaces.h define control board standard interfaces*/

namespace yarp {
    namespace dev {
        class IPidControlRaw;
        class IPidControl;
        class IPositionControlRaw;
        class IPositionControl;
        class IEncodersRaw;
        class IEncoders;
        class ITorqueControlRaw;
        class IVelocityControlRaw;
        class IVelocityControl;
        class IAmplifierControlRaw;
        class IAmplifierControl;
        class IControlDebug;
        class IControlLimitsRaw;
        class IControlLimits;
        class IControlCalibrationRaw;
        class IControlCalibration2Raw;
        class IControlCalibration;
        class IControlCalibration2;
    }
}


/**
 * @ingroup dev_iface_motor
 *
 * Interface for a generic control board device implementing a PID controller.
 */
class yarp::dev::IPidControlRaw
{
public:
    /**
     * Destructor.
     */
    virtual ~IPidControlRaw() {}

    /** Set new pid value for a joint axis.
     * @param j joint number
     * @param pid new pid value
     * @return true/false on success/failure
     */
    virtual bool setPidRaw(int j, const Pid &pid)=0;

    /** Set new pid value on multiple axes.
     * @param pids pointer to a vector of pids
     * @return true/false upon success/failure
     */
    virtual bool setPidsRaw(const Pid *pids)=0;

    /** Set the controller reference point for a given axis.
     * Warning this method can result in very large torques 
     * and should be used carefully. If you do not understand
     * this warning you should avoid using this method. 
     * Have a look at other interfaces (e.g. position control).
     * @param j joint number
     * @param ref new reference point
     * @return true/false upon success/failure
     */
    virtual bool setReferenceRaw(int j, double ref)=0;

    /** Set the controller reference points, multiple axes.
     * Warning this method can result in very large torques 
     * and should be used carefully. If you do not understand
     * this warning you should avoid using this method. 
     * Have a look at other interfaces (e.g. position control).
     * @param refs pointer to the vector that contains the new reference points.
     * @return true/false upon success/failure
     */
    virtual bool setReferencesRaw(const double *refs)=0;

    /** Set the error limit for the controller on a specifi joint
     * @param j joint number
     * @param limit limit value
     * @return true/false on success/failure
     */
    virtual bool setErrorLimitRaw(int j, double limit)=0;

    /** Get the error limit for the controller on all joints.
     * @param limits pointer to the vector with the new limits
     * @return true/false on success/failure
     */
    virtual bool setErrorLimitsRaw(const double *limits)=0;

    /** Get the current error for a joint.
     * @param j joint number
     * @param err pointer to the storage for the return value
     * @return true/false on success failure
     */
    virtual bool getErrorRaw(int j, double *err)=0;

    /** Get the error of all joints.
     * @param errs pointer to the vector that will store the errors
     */
    virtual bool getErrorsRaw(double *errs)=0;

    /** Get the output of the controller (e.g. pwm value)
     * @param j joint number
     * @param out pointer to storage for return value
     * @return success/failure
     */
    virtual bool getOutputRaw(int j, double *out)=0;

    /** Get the output of the controllers (e.g. pwm value)
     * @param outs pinter to the vector that will store the output values
     */
    virtual bool getOutputsRaw(double *outs)=0;

    /** Get current pid value for a specific joint.
     * @param j joint number
     * @param pid pointer to storage for the return value.
     * @return success/failure
     */
    virtual bool getPidRaw(int j, Pid *pid)=0;

    /** Get current pid value for a specific joint.
     * @param pids vector that will store the values of the pids.
     * @return success/failure
     */
    virtual bool getPidsRaw(Pid *pids)=0;

    /** Get the current reference position of the controller for a specific joint.
     * @param j joint number
     * @param ref pointer to storage for return value
     * @return reference value 
     */
    virtual bool getReferenceRaw(int j, double *ref)=0;

    /** Get the current reference position of all controllers.
     * @param refs vector that will store the output.
     */
    virtual bool getReferencesRaw(double *refs)=0;

    /** Get the error limit for the controller on a specific joint
     * @param j joint number
     * @param limit pointer to storage
     * @return success/failure
     */
    virtual bool getErrorLimitRaw(int j, double *limit)=0;

    /** Get the error limit for all controllers
     * @param limits pointer to the array that will store the output
     * @return success or failure
     */
    virtual bool getErrorLimitsRaw(double *limits)=0;

    /** Reset the controller of a given joint, usually sets the 
     * current position of the joint as the reference value for the PID, and resets
     * the integrator.
     * @param j joint number
     * @return true on success, false on failure.
     */
    virtual bool resetPidRaw(int j)=0;

    /** Disable the pid computation for a joint*/
    virtual bool disablePidRaw(int j)=0;

    /** Enable the pid computation for a joint*/
    virtual bool enablePidRaw(int j)=0;

	/** Set offset value for a given pid*/
    virtual bool setOffsetRaw(int j, double v)=0;
};

/**
 * @ingroup dev_iface_motor
 *
 * Interface for a generic control board device implementing a PID controller,
 * with scaled arguments.
 */
class yarp::dev::IPidControl
{
public:
    /**
     * Destructor.
     */
    virtual ~IPidControl() {}

    /** Set new pid value for a joint axis.
     * @param j joint number
     * @param pid new pid value
     * @return true/false on success/failure
     */
    virtual bool setPid(int j, const Pid &pid)=0;

    /** Set new pid value on multiple axes.
     * @param pids pointer to a vector of pids
     * @return true/false upon success/failure
     */
    virtual bool setPids(const Pid *pids)=0;

    /** Set the controller reference point for a given axis.
     * Warning this method can result in very large torques 
     * and should be used carefully. If you do not understand
     * this warning you should avoid using this method. 
     * Have a look at other interfaces (e.g. position control).
     * @param j joint number
     * @param ref new reference point
     * @return true/false upon success/failure
     */
    virtual bool setReference(int j, double ref)=0;

    /** Set the controller reference points, multiple axes.
     * Warning this method can result in very large torques 
     * and should be used carefully. If you do not understand
     * this warning you should avoid using this method. 
     * Have a look at other interfaces (e.g. position control).
     * @param refs pointer to the vector that contains the new reference points.
     * @return true/false upon success/failure
     */
    virtual bool setReferences(const double *refs)=0;

    /** Set the error limit for the controller on a specifi joint
     * @param j joint number
     * @param limit limit value
     * @return true/false on success/failure
     */
    virtual bool setErrorLimit(int j, double limit)=0;

    /** Get the error limit for the controller on all joints.
     * @param limits pointer to the vector with the new limits
     * @return true/false on success/failure
     */
    virtual bool setErrorLimits(const double *limits)=0;

    /** Get the current error for a joint.
     * @param j joint number
     * @param err pointer to the storage for the return value
     * @return true/false on success failure
     */
    virtual bool getError(int j, double *err)=0;

    /** Get the error of all joints.
     * @param errs pointer to the vector that will store the errors
     */
    virtual bool getErrors(double *errs)=0;

    /** Get the output of the controller (e.g. pwm value)
     * @param j joint number
     * @param out pointer to storage for return value
     * @return success/failure
     */
    virtual bool getOutput(int j, double *out)=0;

    /** Get the output of the controllers (e.g. pwm value)
     * @param outs pinter to the vector that will store the output values
     */
    virtual bool getOutputs(double *outs)=0;

    /** Get current pid value for a specific joint.
     * @param j joint number
     * @param pid pointer to storage for the return value.
     * @return success/failure
     */
    virtual bool getPid(int j, Pid *pid)=0;

    /** Get current pid value for a specific joint.
     * @param pids vector that will store the values of the pids.
     * @return success/failure
     */
    virtual bool getPids(Pid *pids)=0;

    /** Get the current reference position of the controller for a specific joint.
     * @param j joint number
     * @param ref pointer to storage for return value
     * @return reference value 
     */
    virtual bool getReference(int j, double *ref)=0;

    /** Get the current reference position of all controllers.
     * @param refs vector that will store the output.
     */
    virtual bool getReferences(double *refs)=0;

    /** Get the error limit for the controller on a specific joint
     * @param j joint number
     * @param limit pointer to storage
     * @return success/failure
     */
    virtual bool getErrorLimit(int j, double *limit)=0;

    /** Get the error limit for all controllers
     * @param limits pointer to the array that will store the output
     * @return success or failure
     */
    virtual bool getErrorLimits(double *limits)=0;

    /** Reset the controller of a given joint, usually sets the 
     * current position of the joint as the reference value for the PID, and resets
     * the integrator.
     * @param j joint number
     * @return true on success, false on failure.
     */
    virtual bool resetPid(int j)=0;

    /** Disable the pid computation for a joint*/
    virtual bool disablePid(int j)=0;

    /** Enable the pid computation for a joint*/
    virtual bool enablePid(int j)=0;

	/** Set offset value for a given controller*/
    virtual bool setOffset(int j, double v)=0;
};

/**
 * @ingroup dev_iface_motor
 *
 * Interface for a generic control board device implementing position control in encoder
 * coordinates.
 */
class yarp::dev::IPositionControlRaw
{
public:
    /**
     * Destructor.
     */
    virtual ~IPositionControlRaw() {}

    /**
     * Get the number of controlled axes. This command asks the number of controlled
     * axes for the current physical interface.
     * @param ax storage to return param
     * @return true/false.
     */
    virtual bool getAxes(int *ax) = 0;

    /** Set position mode. This command
     * is required by control boards implementing different
     * control methods (e.g. velocity/torque), in some cases
     * it can be left empty.
     * return true/false on success failure
     */
    virtual bool setPositionMode()=0;

    /** Set new reference point for a single axis.
     * @param j joint number
     * @param ref specifies the new ref point
     * @return true/false on success/failure
     */
    virtual bool positionMoveRaw(int j, double ref)=0;

    /** Set new reference point for all axes.
     * @param refs array, new reference points.
     * @return true/false on success/failure
     */
    virtual bool positionMoveRaw(const double *refs)=0;

    /** Set relative position. The command is relative to the 
     * current position of the axis.
     * @param j joint axis number
     * @param delta relative command
     * @return true/false on success/failure
     */
    virtual bool relativeMoveRaw(int j, double delta)=0;

    /** Set relative position, all joints.
     * @param deltas pointer to the relative commands
     * @return true/false on success/failure
     */
    virtual bool relativeMoveRaw(const double *deltas)=0;

    /** Check if the current trajectory is terminated. Non blocking.
	 * @param j is the axis number
	 * @param flag is a pointer to return value
	 * @return true/false on success/failure
     */
    virtual bool checkMotionDoneRaw(int j, bool *flag)=0;

    /** Check if the current trajectory is terminated. Non blocking.
	 * @param flag is a pointer to return value ("and" of all joints)
	 * @return true/false on success/failure
     */
    virtual bool checkMotionDoneRaw(bool *flag)=0;

    /** Set reference speed for a joint, this is the speed used during the
     * interpolation of the trajectory.
     * @param j joint number
     * @param sp speed value
     * @return true/false upon success/failure
     */
    virtual bool setRefSpeedRaw(int j, double sp)=0;

    /** Set reference speed on all joints. These values are used during the
     * interpolation of the trajectory.
     * @param spds pointer to the array of speed values.
     * @return true/false upon success/failure
     */
    virtual bool setRefSpeedsRaw(const double *spds)=0;

    /** Set reference acceleration for a joint. This value is used during the
     * trajectory generation.
     * @param j joint number
     * @param acc acceleration value
     * @return true/false upon success/failure
     */
    virtual bool setRefAccelerationRaw(int j, double acc)=0;

    /** Set reference acceleration on all joints. This is the valure that is
     * used during the generation of the trajectory.
     * @param accs pointer to the array of acceleration values
     * @return true/false upon success/failure
     */
    virtual bool setRefAccelerationsRaw(const double *accs)=0;

    /** Get reference speed for a joint. Returns the speed used to 
     * generate the trajectory profile.
     * @param j joint number
     * @param ref pointer to storage for the return value
     * @return true/false on success or failure
     */
    virtual bool getRefSpeedRaw(int j, double *ref)=0;

    /** Get reference speed of all joints. These are the  values used during the
     * interpolation of the trajectory.
     * @param spds pointer to the array that will store the speed values.
     */
    virtual bool getRefSpeedsRaw(double *spds)=0;

    /** Get reference acceleration for a joint. Returns the acceleration used to 
     * generate the trajectory profile.
     * @param j joint number
     * @param acc pointer to storage for the return value
     * @return true/false on success/failure
     */
    virtual bool getRefAccelerationRaw(int j, double *acc)=0;

    /** Get reference acceleration of all joints. These are the values used during the
     * interpolation of the trajectory.
     * @param accs pointer to the array that will store the acceleration values.
     * @return true/false on success or failure 
     */
    virtual bool getRefAccelerationsRaw(double *accs)=0;

    /** Stop motion, single joint
     * @param j joint number
     * @return true/false on success/failure
     */
    virtual bool stopRaw(int j)=0;

    /** Stop motion, multiple joints 
     * @return true/false on success/failure
     */
    virtual bool stopRaw()=0;
};

/**
 * @ingroup dev_iface_motor
 *
 * Interface for a generic control board device implementing position control.
 */
class yarp::dev::IPositionControl
{
public:
    /**
     * Destructor.
     */
    virtual ~IPositionControl() {}

    /**
     * Get the number of controlled axes. This command asks the number of controlled
     * axes for the current physical interface.
     * @param ax pointer to storage
     * @return true/false.
     */
    virtual bool getAxes(int *ax) = 0;

    /** Set position mode. This command
     * is required by control boards implementing different
     * control methods (e.g. velocity/torque), in some cases
     * it can be left empty.
     * return true/false on success/failure
     */
    virtual bool setPositionMode()=0;

    /** Set new reference point for a single axis.
     * @param j joint number
     * @param ref specifies the new ref point
     * @return true/false on success/failure
     */
    virtual bool positionMove(int j, double ref)=0;

    /** Set new reference point for all axes.
     * @param refs array, new reference points.
     * @return true/false on success/failure
     */
    virtual bool positionMove(const double *refs)=0;

    /** Set relative position. The command is relative to the 
     * current position of the axis.
     * @param j joint axis number
     * @param delta relative command
     * @return true/false on success/failure
     */
    virtual bool relativeMove(int j, double delta)=0;

    /** Set relative position, all joints.
     * @param deltas pointer to the relative commands
     * @return true/false on success/failure
     */
    virtual bool relativeMove(const double *deltas)=0;

    /** Check if the current trajectory is terminated. Non blocking.
     * @return true if the trajectory is terminated, false otherwise
     */
    virtual bool checkMotionDone(int j, bool *flag)=0;

    /** Check if the current trajectory is terminated. Non blocking.
     * @return true if the trajectory is terminated, false otherwise
     */
    virtual bool checkMotionDone(bool *flag)=0;

    /** Set reference speed for a joint, this is the speed used during the
     * interpolation of the trajectory.
     * @param j joint number
     * @param sp speed value
     * @return true/false upon success/failure
     */
    virtual bool setRefSpeed(int j, double sp)=0;

    /** Set reference speed on all joints. These values are used during the
     * interpolation of the trajectory.
     * @param spds pointer to the array of speed values.
     * @return true/false upon success/failure
     */
    virtual bool setRefSpeeds(const double *spds)=0;

    /** Set reference acceleration for a joint. This value is used during the
     * trajectory generation.
     * @param j joint number
     * @param acc acceleration value
     * @return true/false upon success/failure
     */
    virtual bool setRefAcceleration(int j, double acc)=0;

    /** Set reference acceleration on all joints. This is the valure that is
     * used during the generation of the trajectory.
     * @param accs pointer to the array of acceleration values
     * @return true/false upon success/failure
     */
    virtual bool setRefAccelerations(const double *accs)=0;

    /** Get reference speed for a joint. Returns the speed used to 
     * generate the trajectory profile.
     * @param j joint number
     * @param ref pointer to storage for the return value
     * @return true/false on success or failure
     */
    virtual bool getRefSpeed(int j, double *ref)=0;

    /** Get reference speed of all joints. These are the  values used during the
     * interpolation of the trajectory.
     * @param spds pointer to the array that will store the speed values.
     */
    virtual bool getRefSpeeds(double *spds)=0;

    /** Get reference acceleration for a joint. Returns the acceleration used to 
     * generate the trajectory profile.
     * @param j joint number
     * @param acc pointer to storage for the return value
     * @return true/false on success/failure
     */
    virtual bool getRefAcceleration(int j, double *acc)=0;

    /** Get reference acceleration of all joints. These are the values used during the
     * interpolation of the trajectory.
     * @param accs pointer to the array that will store the acceleration values.
     * @return true/false on success or failure 
     */
    virtual bool getRefAccelerations(double *accs)=0;

    /** Stop motion, single joint
     * @param j joint number
     * @return true/false on success/failure
     */
    virtual bool stop(int j)=0;

    /** Stop motion, multiple joints 
     * @return true/false on success/failure
     */
    virtual bool stop()=0;
};

/**
 * @ingroup dev_iface_motor
 *
 * Interface for control boards implementig velocity control in encoder coordinates.
 */
class yarp::dev::IVelocityControlRaw
{
public:
    /**
     * Destructor.
     */
    virtual ~IVelocityControlRaw() {}

    /**
     * Get the number of controlled axes. This command asks the number of controlled
     * axes for the current physical interface.
     * @param axis pointer to storage, return value
     * @return true/false.
     */
    virtual bool getAxes(int *axis) = 0;

    /**
     * Set position mode. This command
     * is required by control boards implementing different
     * control methods (e.g. velocity/torque), in some cases
     * it can be left empty.
     * @return true/false on success failure
     */
    virtual bool setVelocityMode()=0;

    /**
     * Start motion at a given speed, single joint.
     * @param j joint number
     * @param sp speed value
     * @return bool/false upone success/failure
     */
    virtual bool velocityMoveRaw(int j, double sp)=0;

    /**
     * Start motion at a given speed, multiple joints.
     * @param sp pointer to the array containing the new speed values
     * @return true/false upon success/failure
     */
    virtual bool velocityMoveRaw(const double *sp)=0;

    /** Set reference acceleration for a joint. This value is used during the
     * trajectory generation.
     * @param j joint number
     * @param acc acceleration value
     * @return true/false upon success/failure
     */
    virtual bool setRefAccelerationRaw(int j, double acc)=0;

    /** Set reference acceleration on all joints. This is the valure that is
     * used during the generation of the trajectory.
     * @param accs pointer to the array of acceleration values
     * @return true/false upon success/failure
     */
    virtual bool setRefAccelerationsRaw(const double *accs)=0;
 
    /** Get reference acceleration for a joint. Returns the acceleration used to 
     * generate the trajectory profile.
     * @param j joint number
     * @param acc pointer to storage for the return value
     * @return true/false on success/failure
     */
    virtual bool getRefAccelerationRaw(int j, double *acc)=0;

    /** Get reference acceleration of all joints. These are the values used during the
     * interpolation of the trajectory.
     * @param accs pointer to the array that will store the acceleration values.
     * @return true/false on success or failure 
     */
    virtual bool getRefAccelerationsRaw(double *accs)=0;

    /** Stop motion, single joint
     * @param j joint number
     * @return true/false on success or failure
     */
    virtual bool stopRaw(int j)=0;

    /** Stop motion, multiple joints 
     * @return true/false on success or failure
     */
    virtual bool stopRaw()=0;
};

/**
 * @ingroup dev_iface_motor
 *
 * Interface for control boards implementing velocity control.
 */
class yarp::dev::IVelocityControl
{
public:
    /**
     * Destructor.
     */
    virtual ~IVelocityControl() {}

    /**
     * Get the number of controlled axes. This command asks the number of controlled
     * axes for the current physical interface.
     * parame axes pointer to storage
     * @return true/false.
     */
    virtual bool getAxes(int *axes) = 0;

    /**
     * Set position mode. This command
     * is required by control boards implementing different
     * control methods (e.g. velocity/torque), in some cases
     * it can be left empty.
     * @return true/false on success failure
     */
    virtual bool setVelocityMode()=0;

    /**
     * Start motion at a given speed, single joint.
     * @param j joint number
     * @param sp speed value
     * @return bool/false upone success/failure
     */
    virtual bool velocityMove(int j, double sp)=0;

    /**
     * Start motion at a given speed, multiple joints.
     * @param sp pointer to the array containing the new speed values
     * @return true/false upon success/failure
     */
    virtual bool velocityMove(const double *sp)=0;

    /** Set reference acceleration for a joint. This value is used during the
     * trajectory generation.
     * @param j joint number
     * @param acc acceleration value
     * @return true/false upon success/failure
     */
    virtual bool setRefAcceleration(int j, double acc)=0;

    /** Set reference acceleration on all joints. This is the valure that is
     * used during the generation of the trajectory.
     * @param accs pointer to the array of acceleration values
     * @return true/false upon success/failure
     */
    virtual bool setRefAccelerations(const double *accs)=0;
 
    /** Get reference acceleration for a joint. Returns the acceleration used to 
     * generate the trajectory profile.
     * @param j joint number
     * @param acc pointer to storage for the return value
     * @return true/false on success/failure
     */
    virtual bool getRefAcceleration(int j, double *acc)=0;

    /** Get reference acceleration of all joints. These are the values used during the
     * interpolation of the trajectory.
     * @param accs pointer to the array that will store the acceleration values.
     * @return true/false on success or failure 
     */
    virtual bool getRefAccelerations(double *accs)=0;

    /** Stop motion, single joint
     * @param j joint number
     * @return true/false on success or failure
     */
    virtual bool stop(int j)=0;

    /** Stop motion, multiple joints 
     * @return true/false on success or failure
     */
    virtual bool stop()=0;
};

/**
 * @ingroup dev_iface_motor
 *
 * Interface for control boards implementing torque control.
 */
class yarp::dev::ITorqueControlRaw
{
public:
    /**
     * Destructor.
     */
    virtual ~ITorqueControlRaw() {}

    /**
     * Get the number of controlled axes. This command asks the number of controlled
     * axes for the current physical interface.
     * @return the number of controlled axes.
     */
    virtual bool getAxes(int *ax) = 0;

    /**
     * Set torque control mode. This command
     * is required by control boards implementing different
     * control methods (e.g. velocity/torque), in some cases
     * it can be left empty.
     * @return true/false on success failure
     */
    virtual bool setTorqueMode()=0;

    /** Get the value of the torque on a given joint.
     * @param j joint number
     * @return torque value
     */
    virtual double getRefTorqueRaw(int j)=0;

    /** Get the value of the torque for all joints.
     * @param t pointer to the array that will store the output
     */
    virtual void getRefTorquesRaw(double *t)=0;

    /** Set the reference value of the torque for all joints.
     * @param t pointer to the array of torque values
     * @return true/false
     */
    virtual bool setTorquesRaw(const double *t)=0;

    /** Set the reference value of the torque for a given joint.
     * @param j joint number
     * @param t new value
     */
    virtual void setTorqueRaw(int j, double t)=0;
};

/**
 * @ingroup dev_iface_motor
 *
 * Control board, encoder interface.
 */
class yarp::dev::IEncodersRaw
{
public:
    /**
     * Destructor.
     */
    virtual ~IEncodersRaw() {}

    /**
     * Get the number of controlled axes. This command asks the number of controlled
     * axes for the current physical interface.
     * @return the number of controlled axes.
     */
    virtual bool getAxes(int *ax) = 0;

    /**
     * Reset encoder, single joint. Set the encoder value to zero 
     * @param j encoder number
     * @return true/false
     */
    virtual bool resetEncoderRaw(int j)=0;

    /**
     * Reset encoders. Set the encoders value to zero 
     * @return true/false
     */
    virtual bool resetEncodersRaw()=0;

    /**
     * Set the value of the encoder for a given joint. 
     * @param j encoder number
     * @param val new value
     * @return true/false
     */
    virtual bool setEncoderRaw(int j, double val)=0;

    /**
     * Set the value of all encoders.
     * @param vals pointer to the new values
     * @return true/false
     */
    virtual bool setEncodersRaw(const double *vals)=0;

    /**
     * Read the value of an encoder.
     * @param j encoder number
     * @param v pointer to storage for the return value
     * @return true/false, upon success/failure (you knew it, uh?)
     */
    virtual bool getEncoderRaw(int j, double *v)=0;

    /**
     * Read the position of all axes.
     * @param encs pointer to the array that will contain the output
     * @return true/false on success/failure
     */
    virtual bool getEncodersRaw(double *encs)=0;

    /**
     * Read the instantaneous speed of an axis.
     * @param j axis number
     * @param sp pointer to storage for the output
     * @return true if successful, false ... otherwise.
     */
    virtual bool getEncoderSpeedRaw(int j, double *sp)=0;

    /**
     * Read the instantaneous acceleration of an axis.
     * @param spds pointer to storage for the output values
     * @return guess what? (true/false on success or failure).
     */
    virtual bool getEncoderSpeedsRaw(double *spds)=0;
    
    /**
     * Read the instantaneous acceleration of an axis.
     * @param j axis number
     * @param spds pointer to the array that will contain the output
     */
    virtual bool getEncoderAccelerationRaw(int j, double *spds)=0;

    /**
     * Read the instantaneous acceleration of all axes.
     * @param accs pointer to the array that will contain the output
     * @return true if all goes well, false if anything bad happens. 
     */
    virtual bool getEncoderAccelerationsRaw(double *accs)=0;
};

/**
 * @ingroup dev_iface_motor
 *
 * Control board, encoder interface.
 */
class yarp::dev::IEncoders
{
public:
    /**
     * Destructor.
     */
    virtual ~IEncoders() {}

    /**
     * Get the number of controlled axes. This command asks the number of controlled
     * axes for the current physical interface.
     * @return the number of controlled axes.
     */
    virtual bool getAxes(int *ax) = 0;

    /**
     * Reset encoder, single joint. Set the encoder value to zero 
     * @param j encoder number
     * @return true/false
     */
    virtual bool resetEncoder(int j)=0;

    /**
     * Reset encoders. Set the encoders value to zero 
     * @return true/false
     */
    virtual bool resetEncoders()=0;

    /**
     * Set the value of the encoder for a given joint. 
     * @param j encoder number
     * @param val new value
     * @return true/false
     */
    virtual bool setEncoder(int j, double val)=0;

    /**
     * Set the value of all encoders.
     * @param vals pointer to the new values
     * @return true/false
     */
    virtual bool setEncoders(const double *vals)=0;

    /**
     * Read the value of an encoder.
     * @param j encoder number
     * @param v pointer to storage for the return value
     * @return true/false, upon success/failure (you knew it, uh?)
     */
    virtual bool getEncoder(int j, double *v)=0;

    /**
     * Read the position of all axes.
     * @param encs pointer to the array that will contain the output
     * @return true/false on success/failure
     */
    virtual bool getEncoders(double *encs)=0;

    /**
     * Read the istantaneous speed of an axis.
     * @param j axis number
     * @param sp pointer to storage for the output
     * @return true if successful, false ... otherwise.
     */
    virtual bool getEncoderSpeed(int j, double *sp)=0;

    /**
     * Read the instantaneous speed of all axes.
     * @param spds pointer to storage for the output values
     * @return guess what? (true/false on success or failure).
     */
    virtual bool getEncoderSpeeds(double *spds)=0;
    
    /**
     * Read the instantaneous acceleration of an axis.
     * @param j axis number
     * @param spds pointer to the array that will contain the output
     */
    virtual bool getEncoderAcceleration(int j, double *spds)=0;

    /**
     * Read the instantaneous acceleration of all axes.
     * @param accs pointer to the array that will contain the output
     * @return true if all goes well, false if anything bad happens. 
     */
    virtual bool getEncoderAccelerations(double *accs)=0;
};

/**
 * @ingroup dev_iface_motor
 *
 * Interface for control devices, amplifier commands.
 */
class yarp::dev::IAmplifierControl
{
public:
    /**
     * Destructor.
     */
    virtual ~IAmplifierControl() {}

    /** Enable the amplifier on a specific joint. Be careful, check that the output
     * of the controller is appropriate (usually zero), to avoid 
     * generating abrupt movements.
     * @return true/false on success/failure
     */
    virtual bool enableAmp(int j)=0;

    /** Disable the amplifier on a specific joint. All computations within the board
     * will be carried out normally, but the output will be disabled.
     * @return true/false on success/failure
     */
    virtual bool disableAmp(int j)=0;

    /* Read the electric current going to all motors.
     * @param vals pointer to storage for the output values
     * @return hopefully true, false in bad luck.
     */
    virtual bool getCurrents(double *vals)=0;

    /* Read the electric current going to a given motor.
     * @param j motor number
     * @param val pointer to storage for the output value
     * @return probably true, might return false in bad times
     */
    virtual bool getCurrent(int j, double *val)=0;

    /* Set the maximum electric current going to a given motor. The behavior 
     * of the board/amplifier when this limit is reached depends on the
     * implementation.
     * @param j motor number
     * @param v the new value
     * @return probably true, might return false in bad times
     */
    virtual bool setMaxCurrent(int j, double v)=0;

    /* Get the status of the amplifiers, coded in a 32 bits integer for
     * each amplifier (at the moment contains only the fault, it will be 
     * expanded in the future).
     * @param st pointer to storage
     * @return true in good luck, false otherwise.
     */
    virtual bool getAmpStatus(int *st)=0;
};

/**
 * @ingroup dev_iface_motor
 *
 * Interface for control devices, amplifier commands.
 */
class yarp::dev::IAmplifierControlRaw
{
public:
    /**
     * Destructor.
     */
    virtual ~IAmplifierControlRaw() {}

    /** Enable the amplifier on a specific joint. Be careful, check that the output
     * of the controller is appropriate (usually zero), to avoid 
     * generating abrupt movements.
     * @return true/false on success/failure
     */
    virtual bool enableAmpRaw(int j)=0;

    /** Disable the amplifier on a specific joint. All computations within the board
     * will be carried out normally, but the output will be disabled.
     * @return true/false on success/failure
     */
    virtual bool disableAmpRaw(int j)=0;

    /* Read the electric current going to all motors.
     * @param vals pointer to storage for the output values
     * @return hopefully true, false in bad luck.
     */
    virtual bool getCurrentsRaw(double *vals)=0;

    /* Read the electric current going to a given motor.
     * @param j motor number
     * @param val pointer to storage for the output value
     * @return probably true, might return false in bad times
     */
    virtual bool getCurrentRaw(int j, double *val)=0;

    /* Set the maximum electric current going to a given motor. The behavior 
     * of the board/amplifier when this limit is reached depends on the
     * implementation.
     * @param j motor number
     * @param v the new value
     * @return probably true, might return false in bad times
     */
    virtual bool setMaxCurrentRaw(int j, double v)=0;

    /* Get the status of the amplifiers, coded in a 32 bits integer for
     * each amplifier (at the moment contains only the fault, it will be 
     * expanded in the future).
     * @param st pointer to storage
     * @return true in good luck, false otherwise.
     */
    virtual bool getAmpStatusRaw(int *st)=0;
};

/** 
 * @ingroup dev_iface_motor
 *
 * Interface for control devices, calibration commands.
 */
class yarp::dev::IControlCalibrationRaw
{
public:
    IControlCalibrationRaw(){};
    /**
     * Destructor.
     */
    virtual ~IControlCalibrationRaw() {}

    /* Start calibration, this method is very often platform
     * specific.
     * @return true/false on success failure
     */
    virtual bool calibrateRaw(int j, double p)=0;

    /* Check if the calibration is terminated, on a particular joint.
     * Non blocking.
     * @return true/false 
     */
    virtual bool doneRaw(int j)=0;

};

/** 
 * @ingroup dev_iface_motor
 *
 * New interface for control devices, calibration commands.
 */
class yarp::dev::IControlCalibration2Raw
{
public:
    IControlCalibration2Raw(){};
    /**
     * Destructor.
     */
    virtual ~IControlCalibration2Raw() {}

    /* Start calibration, this method is very often platform
     * specific.
     * @return true/false on success failure
     */
    virtual bool calibrate2Raw(int axis, unsigned int type, double p1, double p2, double p3)=0;

    /* Check if the calibration is terminated, on a particular joint.
     * Non blocking.
     * @return true/false 
     */
    virtual bool doneRaw(int j)=0;

};

/** 
 * @ingroup dev_iface_motor
 *
 * Interface for control devices, calibration commands.
 */
class yarp::dev::IControlCalibration
{
private:
    ICalibrator *calibrator;

public:
    IControlCalibration();
    /**
     * Destructor.
     */
    virtual ~IControlCalibration() {}

    /* Start calibration, this method is very often platform
     * specific.
     * @return true/false on success failure
     */
    virtual bool calibrate(int j, double p)=0;

    /* Check if the calibration is terminated, on a particular joint.
     * Non blocking.
     * @return true/false 
     */
    virtual bool done(int j)=0;

    /* Set the calibrator object to be used to calibrate the robot.
     * @param c pointer to the calibrator object
     * @return true/false on success failure
     */
    virtual bool setCalibrator(ICalibrator *c);

    /* Calibrate robot by using an external calibrator. The external 
     * calibrator must be previously set by calling the setCalibration()
     * method.
     * @return true/false on success failure
     */
    virtual bool calibrate();

    virtual bool park(bool wait=true);

};

/** 
 * @ingroup dev_iface_motor
 *
 * Interface for control devices, calibration commands.
 */
class yarp::dev::IControlCalibration2
{
private:
    ICalibrator *calibrator;

public:
    IControlCalibration2();
    /**
     * Destructor.
     */
    virtual ~IControlCalibration2() {}

    /* Start calibration, this method is very often platform
     * specific.
     * @return true/false on success failure
     */
    virtual bool calibrate2(int axis, unsigned int type, double p1, double p2, double p3)=0;

    /* Check if the calibration is terminated, on a particular joint.
     * Non blocking.
     * @return true/false 
     */
    virtual bool done(int j)=0;

    /* Set the calibrator object to be used to calibrate the robot.
     * @param c pointer to the calibrator object
     * @return true/false on success failure
     */
    virtual bool setCalibrator(ICalibrator *c);

    /* Calibrate robot by using an external calibrator. The external 
     * calibrator must be previously set by calling the setCalibration()
     * method.
     * @return true/false on success failure
     */
    virtual bool calibrate();

    virtual bool park(bool wait=true);
};

/** 
 * @ingroup dev_iface_motor
 *
 * Interface for control devices, debug commands.
 */
class yarp::dev::IControlDebug
{
public:
    /**
     * Destructor.
     */
    virtual ~IControlDebug() {}

    /* Set the print function, pass here a pointer to your own function 
     * to print. This function should implement "printf" like parameters. 
     * @param a pointer to the print function
     * @return I don't see good reasons why it should return false.
     */
    virtual bool setPrintFunction(int (*f) (const char *fmt, ...))=0;

    /* Read the content of the board internal memory, this is usually done
     * at boot time, but can be forced by calling this method. 
     * @return true/false on success failure
     */
    virtual bool loadBootMemory()=0;
    
    /* Save the current board configuration to the internal memory,
     * this values are read at boot time or if loadBootMemory() is called.
     * @return true/false on success/failure
     */
    virtual bool saveBootMemory()=0;
};

/** 
 * @ingroup dev_iface_motor
 *
 * Interface for control devices, limits commands.
 */
class yarp::dev::IControlLimits
{
public:
    /**
     * Destructor.
     */
    virtual ~IControlLimits() {}

    /* Set the software limits for a particular axis, the behavior of the
     * control card when these limits are exceeded, depends on the implementation.
     * @param axis joint number (why am I telling you this)
     * @param min the value of the lower limit
     * @param max the value of the upper limit
     * @return true or false on success or failure
     */
    virtual bool setLimits(int axis, double min, double max)=0;
    
    /* Get the software limits for a particular axis.
     * @param axis joint number (again... why am I telling you this)
     * @param pointer to store the value of the lower limit
     * @param pointer to store the value of the upper limit
     * @return true if everything goes fine, false if something bad happens (yes, sometimes life is tough)
     */
    virtual bool getLimits(int axis, double *min, double *max)=0;
};

/** 
 * Interface for control devices. Limits commands.
 */
class yarp::dev::IControlLimitsRaw
{
public:
    /**
     * Destructor.
     */
    virtual ~IControlLimitsRaw() {}

    /* Set the software limits for a particular axis, the behavior of the
     * control card when these limits are exceeded, depends on the implementation.
     * @param axis joint number (why am I telling you this)
     * @param min the value of the lower limit
     * @param max the value of the upper limit
     * @return true or false on success or failure
     */
    virtual bool setLimitsRaw(int axis, double min, double max)=0;
    
    /* Get the software limits for a particular axis.
     * @param axis joint number (again... why am I telling you this)
     * @param pointer to store the value of the lower limit
     * @param pointer to store the value of the upper limit
     * @return true if everything goes fine, false if something bad happens (yes, sometimes life is tough)
     */
    virtual bool getLimitsRaw(int axis, double *min, double *max)=0;
};


/* Vocabs representing the above interfaces */

#define VOCAB_SET VOCAB3('s','e','t')
#define VOCAB_GET VOCAB3('g','e','t')
#define VOCAB_IS VOCAB2('i','s')
#define VOCAB_FAILED VOCAB4('f','a','i','l')
#define VOCAB_OK VOCAB2('o','k')

#define VOCAB_OFFSET VOCAB3('o', 'f', 'f')

// interface IPidControl sets.
#define VOCAB_PID VOCAB3('p','i','d')
#define VOCAB_PIDS VOCAB4('p','i','d','s')
#define VOCAB_REF VOCAB3('r','e','f')
#define VOCAB_REFS VOCAB4('r','e','f','s')
#define VOCAB_LIM VOCAB3('l','i','m')
#define VOCAB_LIMS VOCAB4('l','i','m','s')
#define VOCAB_RESET VOCAB3('r','e','s')
#define VOCAB_DISABLE VOCAB3('d','i','s')
#define VOCAB_ENABLE VOCAB3('e','n','a')

// interface IPidControl gets.
#define VOCAB_ERR VOCAB3('e','r','r')
#define VOCAB_ERRS VOCAB4('e','r','r','s')
#define VOCAB_OUTPUT VOCAB3('o','u','t')
#define VOCAB_OUTPUTS VOCAB4('o','u','t','s')
#define VOCAB_REFERENCE VOCAB3('r','e','f')
#define VOCAB_REFERENCES VOCAB4('r','e','f','s')

// interface IPositionControl gets
#define VOCAB_AXES VOCAB4('a','x','e','s')
#define VOCAB_MOTION_DONE VOCAB3('d','o','n')
#define VOCAB_MOTION_DONES VOCAB4('d','o','n','s')

// interface IPositionControl sets
#define VOCAB_POSITION_MODE VOCAB4('p','o','s','d')
#define VOCAB_POSITION_MOVE VOCAB3('p','o','s')
#define VOCAB_POSITION_MOVES VOCAB4('p','o','s','s')
#define VOCAB_RELATIVE_MOVE VOCAB3('r','e','l')
#define VOCAB_RELATIVE_MOVES VOCAB4('r','e','l','s')
#define VOCAB_REF_SPEED VOCAB3('v','e','l')
#define VOCAB_REF_SPEEDS VOCAB4('v','e','l','s')
#define VOCAB_REF_ACCELERATION VOCAB3('a','c','c')
#define VOCAB_REF_ACCELERATIONS VOCAB4('a','c','c','s')
#define VOCAB_STOP VOCAB3('s','t','o')
#define VOCAB_STOPS VOCAB4('s','t','o','s')

// interface IVelocityControl sets
#define VOCAB_VELOCITY_MODE VOCAB4('v','e','l','d')
#define VOCAB_VELOCITY_MOVE VOCAB3('v','m','o')
#define VOCAB_VELOCITY_MOVES VOCAB4('v','m','o','s')

// interface IEncoders sets
#define VOCAB_E_RESET VOCAB3('e','r','e')
#define VOCAB_E_RESETS VOCAB4('e','r','e','s')
#define VOCAB_ENCODER VOCAB3('e','n','c')
#define VOCAB_ENCODERS VOCAB4('e','n','c','s')

// interface IEncoders gets
#define VOCAB_ENCODER_SPEED VOCAB3('e','s','p')
#define VOCAB_ENCODER_SPEEDS VOCAB4('e','s','p','s')
#define VOCAB_ENCODER_ACCELERATION VOCAB3('e','a','c')
#define VOCAB_ENCODER_ACCELERATIONS VOCAB4('e','a','c','s')

// interface IAmplifierControl sets/gets
#define VOCAB_AMP_ENABLE VOCAB3('a','e','n')
#define VOCAB_AMP_DISABLE VOCAB3('a','d','i')
#define VOCAB_AMP_CURRENT VOCAB3('a','c','u')
#define VOCAB_AMP_CURRENTS VOCAB4('a','c','u','s')
#define VOCAB_AMP_MAXCURRENT VOCAB4('m','a','x','c')
#define VOCAB_AMP_STATUS VOCAB4('a','s','t','a')

// interface IControlLimits sets/gets
#define VOCAB_LIMITS VOCAB4('l','l','i','m')


#endif

