// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "Commands/WinchUp.h"
#include "Commands/WinchDown.h"
#include "Commands/DumpCube.h"
#include "Commands/StowClamp.h"
#include "Commands/StowBucket.h"
#include "Commands/GoToSwitch.h"
#include "Commands/GoToScale.h"
#include "Commands/CurvatureDrive.h"
#include "auto/Spin.h"
#include "auto/DriveForward.h"
#include "auto/AutonomousCommand.h"
#include "Commands/ToggleBreaking.h"
#include "motion/MotionProfileCommand.h"
#include "OI.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"
#include "auto/AutonomousCommand.h"
#include "Commands/BucketTiltPosition.h"
#include "Commands/ClampPosition.h"
#include "Commands/ClampTiltPosition.h"
#include "Commands/DriveArmsWithJoystick.h"
#include "Commands/DriveWithJoystick.h"
#include "Commands/UpperTiltPosition.h"
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/WinchUp.h"
#include "Commands/WinchDown.h"
#include "Commands/DumpCube.h"
#include "Commands/StowClamp.h"
#include "Commands/StowBucket.h"
#include "Commands/GoToSwitch.h"
#include "Commands/GoToScale.h"
#include "Commands/ResetEncoders.h"

OI::OI() {
	// Process operator interface input here.
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	controlJoystick.reset(new frc::Joystick(1));

	driveArms.reset(new frc::JoystickButton(controlJoystick.get(), 1)); // %rod
	driveArms->WhileHeld(new DriveArmsWithJoystick());

	toggleClamp.reset(new frc::JoystickButton(controlJoystick.get(), 2));
	toggleClamp->WhenPressed(new ClampPosition(-1));// toggle special see clampPosition.cpp
	clamp2Switch.reset(new frc::JoystickButton(controlJoystick.get(), 3));
	clamp2Switch->WhenPressed(new ClampTiltPosition(215));   // clamp to switch
	clamp2Down.reset(new frc::JoystickButton(controlJoystick.get(), 4));
	clamp2Down->WhenPressed(new ClampTiltPosition(357)); // clamp down to pickup cube
	clamp2Bucket.reset(new frc::JoystickButton(controlJoystick.get(), 5));
	clamp2Bucket->WhenPressed(new ClampTiltPosition(84)); //	clamp to bucket

	goToSwitch.reset(new frc::JoystickButton(controlJoystick.get(), 6));
	goToSwitch->WhenPressed(new GoToSwitch());      // bucket to switch
	goToScale.reset(new frc::JoystickButton(controlJoystick.get(), 7));
	goToScale->WhenPressed(new GoToScale());  // bucket to scale.
	dumpCube.reset(new frc::JoystickButton(controlJoystick.get(), 8));
	dumpCube->WhenPressed(new DumpCube());
	// dump, delay and home bucket
	stowBucket.reset(new frc::JoystickButton(controlJoystick.get(), 9));
	stowBucket->WhenPressed(new StowBucket());  // Stow clamp, then bucket
	winchUp.reset(new frc::JoystickButton(controlJoystick.get(), 10));
	winchUp->WhileHeld(new WinchUp());
	winchDown.reset(new frc::JoystickButton(controlJoystick.get(), 11));
	winchDown->WhileHeld(new WinchDown());

	driveJoystick.reset(new frc::Joystick(0));

// SmartDashboard Buttons
	frc::SmartDashboard::PutData("Clamp Close",new ClampPosition(0));
	frc::SmartDashboard::PutData("Clamp Open", new ClampPosition(220));  // 220 also see ClampPosition.cpp
	frc::SmartDashboard::PutData("Clamp to Home",	new ClampTiltPosition(84));
    frc::SmartDashboard::PutData("Clamp to Switch", new ClampTiltPosition(215));
    frc::SmartDashboard::PutData("Clamp Down", new ClampTiltPosition(357));
    frc::SmartDashboard::PutData("Bucket Zero", new BucketTiltPosition(0));
    frc::SmartDashboard::PutData("Bucket Home", new BucketTiltPosition(-15));
    frc::SmartDashboard::PutData("BucketCarry (100)", new BucketTiltPosition(100));
    frc::SmartDashboard::PutData("Bucket to Switch", new BucketTiltPosition(80));
    frc::SmartDashboard::PutData("Bucket to Scale)", new BucketTiltPosition(205));
    frc::SmartDashboard::PutData("BucketAutoDump", new BucketTiltPosition(200));
    frc::SmartDashboard::PutData("Dump Cube", new DumpCube());
    frc::SmartDashboard::PutData("UpperTilt2Home", new UpperTiltPosition(0));
    frc::SmartDashboard::PutData("UpperTilt2Switch", new UpperTiltPosition(150));
    frc::SmartDashboard::PutData("UpperTilt2Scale", new UpperTiltPosition(430));
    frc::SmartDashboard::PutData("StowClamp", new StowClamp());
    frc::SmartDashboard::PutData("GoToSwitch", new GoToSwitch());
    frc::SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    frc::SmartDashboard::PutData("Winch Up", new WinchUp());
    frc::SmartDashboard::PutData("Winch Down", new WinchDown());
	frc::SmartDashboard::PutData(new CurvatureDrive());
	frc::SmartDashboard::PutData(new DriveWithJoystick());


    frc::SmartDashboard::PutData(new ResetDriveTrainEncoders());
	frc::SmartDashboard::PutData(new ResetClampEncoder());
	frc::SmartDashboard::PutData(new ResetClampTiltEncoder());
	frc::SmartDashboard::PutData(new ResetAllEncoders());

    frc::SmartDashboard::PutData(new Spin());
    frc::SmartDashboard::PutNumber("fwd", 12.0);
    frc::SmartDashboard::PutData(new DriveForward(48.0));
	frc::SmartDashboard::PutData(new DumbDriveForward());
	frc::SmartDashboard::PutData(new DriveForwardGyroEncoder());
    frc::SmartDashboard::PutData(new AutonomousCommand());
    frc::SmartDashboard::PutData(new MotionProfileCommand());

}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<frc::Joystick> OI::getDriveJoystick() {
   return driveJoystick;
}

std::shared_ptr<frc::Joystick> OI::getControlJoystick() {
   return controlJoystick;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
