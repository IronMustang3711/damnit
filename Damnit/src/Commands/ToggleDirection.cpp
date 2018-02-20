//
// Created by Jason Markham on 2/16/18.
//

#include <RobotMap.h>
#include <Robot.h>
#include "ToggleDirection.h"

ToggleDirection::ToggleDirection() : frc::InstantCommand("toggle direction") {
}

void ToggleDirection::Initialize() {
    //RobotMap::chassisLeftSide->SetInverted(!RobotMap::chassisLeftSide->GetInverted());
    //RobotMap::chassisRightSide->SetInverted(!RobotMap::chassisRightSide->GetInverted());
    Robot::chassis->toggleDirection();
   // DriverStation::ReportError("toggle");
}
