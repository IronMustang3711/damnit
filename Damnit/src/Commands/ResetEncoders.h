/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Commands/InstantCommand.h>
#include <Commands/CommandGroup.h>

class ResetDriveTrainEncoders : public frc::InstantCommand {
public:
	ResetDriveTrainEncoders();
	void Execute() override;

};
class ResetBucketEncoder : public frc::InstantCommand {
public:
	ResetBucketEncoder();
	void Execute() override;

};
class ResetClampEncoder : public frc::InstantCommand {
public:
	ResetClampEncoder();
	void Execute() override;

};
class ResetClampTiltEncoder : public frc::InstantCommand {
public:
	ResetClampTiltEncoder();
	void Execute() override;

};

class ResetAllEncoders : public frc::CommandGroup {
public:
	ResetAllEncoders();
};


