// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef CLAMPTILTPOSITION_H
#define CLAMPTILTPOSITION_H


#include <Commands/Command.h>

namespace clamp_tilt {
    struct Config {
        double cube_setpoint = 336.0;
        double bucket_setpoint = 82.0;
        double switch_setpoint = 206.0;
    };
    constexpr Config COMPETITION_CONFIG{};
    constexpr Config PROTO_CONFIG{322.0, 82.0, 215.0};

    const Config &getConfig();
}

/**
 *
 *
 * @author ExampleAuthor
 */
class ClampTiltPosition : public frc::Command {

protected:
    explicit ClampTiltPosition(double setpoint);

public:
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

    void Initialize() override;

    void Execute() override;

    bool IsFinished() override;

    void End() override;

    void Interrupted() override;

private:
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=VARIABLES
    double m_setpoint;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=VARIABLES
    // the following is for ramp control and stalled shutoff
    double startTime = 0;
    double prevTime = 0;
    double prevPosition = 0;
    double holdPower;  // this is 20% of max power
    double maxPower;
    double maxVelocity;  // encoder counts per second (about 1/3 rev/sec
    double targetVelocity;  // usually 1/2 maxVelocity;
    double velocityP;  // proportional control
    double velocityFF;  // feedforward control
    double acceleration;  // accel to 300 counts/sec in one second
    double deceleration;
    double PIDband;  // switch to PID when within this band.
    bool velocityControl = false;  // velocity or PID distance control

};

class ClampTiltToSwitch : public ClampTiltPosition {
public:
    ClampTiltToSwitch();
};

class ClampTiltToBucket : public ClampTiltPosition {
public:
    ClampTiltToBucket();
};

class ClampTiltToCube : public ClampTiltPosition {
public:
    ClampTiltToCube();
};

//class ClampTiltToggle : public ClampTiltPosition {
//public:
//    ClampTiltToggle();
//};

class ClampTiltToHome : public ClampTiltPosition {
public:
    ClampTiltToHome();
};

#endif
