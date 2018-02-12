// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "DriveArmsWithJoystick.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

DriveArmsWithJoystick::DriveArmsWithJoystick(): frc::Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::upperTilt.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void DriveArmsWithJoystick::Initialize() {
	Robot::upperTilt->Disable();
}

// Called repeatedly when this Command is scheduled to run
void DriveArmsWithJoystick::Execute() {
	float xAxis = Robot::oi->getControlJoystick()->GetRawAxis(0);
	float yAxis = Robot::oi->getControlJoystick()->GetRawAxis(1);
	SmartDashboard::PutNumber("joyX",xAxis);
	SmartDashboard::PutNumber("joyY",yAxis);
	Robot::upperTilt->upperMotor->Set(yAxis);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveArmsWithJoystick::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void DriveArmsWithJoystick::End() {
	Robot::upperTilt->upperMotor->Set(0);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveArmsWithJoystick::Interrupted() {
  End();
}