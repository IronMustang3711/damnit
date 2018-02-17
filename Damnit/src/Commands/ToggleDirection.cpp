//
// Created by Jason Markham on 2/16/18.
//

#include <RobotMap.h>
#include "ToggleDirection.h"

ToggleDirection::ToggleDirection() : frc::InstantCommand("toggle direction") {
    RobotMap::chassisLeftSide->SetInverted(!RobotMap::chassisLeftSide->GetInverted());
    RobotMap::chassisRightSide->SetInverted(!RobotMap::chassisRightSide->GetInverted());

}
