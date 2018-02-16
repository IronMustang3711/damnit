// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include <Robot.h>
#include "DriveForward.h"
#include "Commands/GoToSwitch.h"
#include "Commands/DumpCube.h"
#include "Spin.h"


AutonomousCommand::AutonomousCommand() : frc::CommandGroup("AUTO(probably wont work)") {
    Requires(Robot::chassis.get());
    Requires(Robot::clamp.get());
    Requires(Robot::clampTilt.get());
    Requires(Robot::bucket.get());
    Requires(Robot::upperTilt.get());

    AddSequential(new DriveForward(60.0));


    AddSequential(new GoToSwitch());
    AddSequential(new DumpCube());


    AddSequential(new DriveForward(-12.0));
    AddSequential(new Spin());

}

void AutonomousCommand::End() {
	Robot::bucket->Disable();
	Robot::upperTilt->Disable();
	Robot::clampTilt->Disable();
	Robot::clamp->Disable();
}
