// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "Commands/PrepWinch.h"
#include "Commands/ToggleDirection.h"
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
#include "auto/MotionProfileCommand.h"
#include "auto/AutoBuilder.h"
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
#include <llvm/raw_ostream.h>
#include <Commands/Command.h>
#include <auto/MotionProfileCommand2.h>
#include <auto/SwitchDumpSequence.h>
#include <auto/ScaleDumpSequence.h>

OI::OI( Commands& commands) {
	llvm::outs() << "OI\n";

	controlJoystick.reset(new frc::Joystick(1));
	driveJoystick.reset(new frc::Joystick(0));

	driveArms.reset(new frc::JoystickButton(controlJoystick.get(), 1)); // %rod
	driveArms->WhileHeld(&commands.driveArmsWithJoystick);

	toggleClamp.reset(new frc::JoystickButton(controlJoystick.get(), 2));
	toggleClamp->WhenPressed(&commands.clampToggle);//(new ClampPosition(-1));// toggle special see clampPosition.cpp
	clamp2Switch.reset(new frc::JoystickButton(controlJoystick.get(), 3));
	clamp2Switch->WhenPressed(&commands.clampTiltToSwitch); //(new ClampTiltPosition(215));   // clamp to switch
	clamp2Down.reset(new frc::JoystickButton(controlJoystick.get(), 4));
	clamp2Down->WhenPressed(&commands.clampTiltToCube); // clamp down to pickup cube
	clamp2Bucket.reset(new frc::JoystickButton(controlJoystick.get(), 5));
	clamp2Bucket->WhenPressed(&commands.clampTiltToBucket); //	clamp to bucket

	goToSwitch.reset(new frc::JoystickButton(controlJoystick.get(), 6));
	goToSwitch->WhenPressed(&commands.goToSwitch);      // bucket to switch
	goToScale.reset(new frc::JoystickButton(controlJoystick.get(), 7));
	goToScale->WhenPressed(&commands.goToScale);  // bucket to scale.
	dumpCube.reset(new frc::JoystickButton(controlJoystick.get(), 8));
	dumpCube->WhenPressed(&commands.dumpCube);
	// dump, delay and home bucket
	stowBucket.reset(new frc::JoystickButton(controlJoystick.get(), 9));
	stowBucket->WhenPressed(&commands.stowBucket);  // Stow clamp, then bucket
	winchUp.reset(new frc::JoystickButton(controlJoystick.get(), 10));
	winchUp->WhileHeld(&commands.winchUp);
	winchDown.reset(new frc::JoystickButton(controlJoystick.get(), 11));
	winchDown->WhileHeld(&commands.winchDown);
	winchPrep.reset(new frc::JoystickButton(driveJoystick.get(),5));
	winchPrep->WhenPressed(&commands.winchPrep);
	dwinchUp.reset(new frc::JoystickButton(driveJoystick.get(), 3));
	dwinchUp->WhileHeld(&commands.winchUp);
	dwinchDown.reset(new frc::JoystickButton(driveJoystick.get(), 4));
	dwinchDown->WhileHeld(&commands.winchDown);

    toggleDirection.reset(new frc::JoystickButton(driveJoystick.get(),2));
    toggleDirection->WhenPressed(&commands.toggleDirection);


//// SmartDashboard Buttons
//	frc::SmartDashboard::PutData("Clamp Close", new ClampClose());//,new ClampPosition(0));
//	frc::SmartDashboard::PutData("Clamp Open",new ClampOpen());// new ClampPosition(220));  // 220 also see ClampPosition.cpp
//	frc::SmartDashboard::PutData("Clamp toggle",new ClampToggle());	//new ClampTiltPosition(84));
//    frc::SmartDashboard::PutData("Clamp tilt to Switch", new ClampTiltToSwitch());//new ClampTiltPosition(215));
//    frc::SmartDashboard::PutData("Clamp tilt to cube",new ClampTiltToCube() );//new ClampTiltPosition(357));
//  //  frc::SmartDashboard::PutData("Bucket Zero", );//new BucketTiltPosition(0));
//    frc::SmartDashboard::PutData("Bucket tilt Home", new BucketTiltAllTheWayBack());//new BucketTiltPosition(-15));
//    frc::SmartDashboard::PutData("Bucket tilt auto level", new BucketTiltAutoLevel());//new BucketTiltPosition(100));
//    frc::SmartDashboard::PutData("Bucket to Switch", new BucketTiltToSwitch());//new BucketTiltPosition(80));
//    frc::SmartDashboard::PutData("Bucket to Scale)",new BucketTiltToScale());// new BucketTiltPosition(205));
//    frc::SmartDashboard::PutData("BucketAutoDump", new BucketTiltAutoLevel());//new BucketTiltPosition(200));
//    frc::SmartDashboard::PutData("Dump Cube", new DumpCube());
//    frc::SmartDashboard::PutData("UpperTilt2Home", new UpperTiltToHome());
//    frc::SmartDashboard::PutData("UpperTilt2Switch", new UpperTiltToSwitch());
//    frc::SmartDashboard::PutData("UpperTilt2Scale", new UpperTiltToScale());
//    frc::SmartDashboard::PutData("StowClamp", new StowClamp());
//    frc::SmartDashboard::PutData("GoToSwitch", new GoToSwitch());
//    frc::SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
   // frc::SmartDashboard::PutData("Winch Up", new WinchUp());
   // frc::SmartDashboard::PutData("Winch Down", new WinchDown());
	frc::SmartDashboard::PutData(new CurvatureDrive());
	frc::SmartDashboard::PutData(new DriveWithJoystick());


    frc::SmartDashboard::PutData(new ResetDriveTrainEncoders());
	//frc::SmartDashboard::PutData(new ResetAllEncoders());
//	frc::SmartDashboard::PutData(new ResetClampEncoder());
//	frc::SmartDashboard::PutData(new ResetClampTiltEncoder());
	frc::SmartDashboard::PutData(new ResetAllEncoders());

   // frc::SmartDashboard::PutData(new Spin());
   // frc::SmartDashboard::PutNumber("fwd", 12.0);
    frc::SmartDashboard::PutData(new DriveForward());
//	frc::SmartDashboard::PutData(new DumbDriveForward());
//	frc::SmartDashboard::PutData(new DriveForwardGyroEncoder());
//    frc::SmartDashboard::PutData(new AutonomousCommand());
//    frc::SmartDashboard::PutData(new AutoBuilder());
   // frc::SmartDashboard::PutData(new MotionProfileCommand());
//	frc::SmartDashboard::PutData(new MotionProfileCommand2());

	frc::SmartDashboard::PutData(new SwitchDumpSequence());
	frc::SmartDashboard::PutData(new ScaleDumpSequence());


}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<frc::Joystick> OI::getDriveJoystick() {
   return driveJoystick;
}

std::shared_ptr<frc::Joystick> OI::getControlJoystick() {
   return controlJoystick;
}


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
