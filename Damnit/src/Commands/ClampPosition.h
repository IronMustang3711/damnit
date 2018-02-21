// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef CLAMPPOSITION_H
#define CLAMPPOSITION_H


#include "Commands/Command.h"

namespace clamp {
    struct Config {
        double open_setpoint = 152.0;
        double open_threshold = 100.0;
        double close_setpoint = 84.0;
        //double switch_setpoint = 206.0;
    };
    constexpr Config COMPETITION_CONFIG{};
    constexpr Config PROTO_CONFIG{220.0, 200.0, 82.0};

    const Config &getConfig();
}

/**
 *
 *
 * @author ExampleAuthor
 */
class ClampPosition : public frc::Command {

protected:
    ClampPosition(double setpoint, double open_threshold);

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
    double open_threshold;
    double clampStartTime;
    bool clampOpen;
};

class ClampOpen : public ClampPosition {
public:
    ClampOpen();
};

class ClampClose : public ClampPosition {
public:
    ClampClose();
};

class ClampToggle : public ClampPosition {
public:
    ClampToggle();
};

#endif
