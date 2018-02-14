/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "ResetEncoders.h"
#include "Robot.h"
#include "Subsystems/Chassis.h"

ResetDriveTrainEncoders::ResetDriveTrainEncoders() : frc::InstantCommand("reset drivetrain encoders") {
	 Requires(Robot::chassis.get());
}
void ResetDriveTrainEncoders::Execute() {
	Robot::chassis->resetEncoders();
}

ResetBucketEncoder::ResetBucketEncoder() : frc::InstantCommand("reset bucket encoder"){
	Requires(Robot::bucket.get());
}
void ResetBucketEncoder::Execute() {
	Robot::bucket->reset();
}

ResetClampEncoder::ResetClampEncoder() : frc::InstantCommand("reset clamp encoder"){
	Requires(Robot::clamp.get());
}
void ResetClampEncoder::Execute() {
	Robot::clamp->reset();
}

ResetClampTiltEncoder::ResetClampTiltEncoder() : frc::InstantCommand("reset clamp tilt encoder") {
	Requires(Robot::clampTilt.get());
}
void ResetClampTiltEncoder::Execute() {
	Robot::clampTilt->reset();
}

ResetAllEncoders::ResetAllEncoders() : frc::CommandGroup("reset all encoders"){
	AddSequential(new ResetDriveTrainEncoders());
	AddSequential(new ResetBucketEncoder());
	AddSequential(new ResetClampEncoder());
	AddSequential(new ResetClampTiltEncoder());
}
