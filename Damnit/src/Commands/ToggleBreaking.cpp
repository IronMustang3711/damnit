/*
 * ToggleBreaking.cpp
 *
 *  Created on: Feb 14, 2018
 *      Author: jason
 */
#include <string>
#include <memory>
#include <Commands/ToggleBreaking.h>
#include <DriverStation.h>
#include "Robot.h"
#include "Subsystems/Chassis.h"
ToggleBreaking::ToggleBreaking() : frc::InstantCommand("Toggle break mode") {
	Requires(Robot::chassis.get());
}

void ToggleBreaking::Execute() {
	enable = !enable;
	std::string msg = enable ? "Enabling" : "Disabling";
	frc::DriverStation::ReportWarning(llvm::Twine(msg)+" neutral drive breaking.");

	Robot::chassis->enableInductiveBreaking(enable);
}
