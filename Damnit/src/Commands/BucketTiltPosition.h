// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef BUCKETTILTPOSITION_H
#define BUCKETTILTPOSITION_H


#include "Commands/Command.h"

namespace bucket_tilt {

    struct Config {
        double home_setpoint = -17;  //TODO test me! possible values: -6, -14,-15,-20
        double winch_prep_setpoint = 212;
        double switch_setpoint = 150;
        double scale_setpoint = 205;
    };
    constexpr Config COMPETITION_CONFIG{};
    constexpr Config PROTO_CONFIG{-15, 217, 150, 205};

    const Config &getConfig();
}


class BucketTiltPosition : public frc::Command {

protected:

    explicit BucketTiltPosition(double setpoint);

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
    double startTime = 0;
    double prevTime = 0;
    double elapsedTime;
    double prevPosition = 0;
    double holdPower;  // this is 20% of max power
    double maxPower;
    double maxVelocity;  // encoder counts per second (about 1/3 rev/sec
    double targetVelocity = 0;  // usually 1/2 maxVelocity;
    double velocityP;  // proportional control
    double velocityFF;  // feedforward control
    double acceleration;  // accel to 300 counts/sec in one second
    double deceleration;
    double PIDband;  // switch to PID when within this band.
    bool velocityControl = false;  // velocity or PID distance control

};

class BucketTiltToSwitch : public BucketTiltPosition {
public:
    BucketTiltToSwitch();
};

class BucketTiltToHome : public BucketTiltPosition {
public:
    BucketTiltToHome();
};

class BucketTiltAutoLevel : public BucketTiltPosition {
public:
    BucketTiltAutoLevel();
};

class BucketTiltToScale : public BucketTiltPosition {
public:
    BucketTiltToScale();
};

class BucketTiltToWinch : public BucketTiltPosition {
public:
    BucketTiltToWinch();
};



#endif
