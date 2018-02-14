/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ResetEncoders.h"
#include "Robot.h"
#include "Subsystems/Chassis.h"

ResetEncoders::ResetEncoders() : frc::InstantCommand("reset encoders") {
	// Use Requires() here to declare subsystem dependencies
	 Requires(Robot::chassis.get());
}



// Called repeatedly when this Command is scheduled to run
void ResetEncoders::Execute() {
	Robot::chassis->ResetEncoders();

}

