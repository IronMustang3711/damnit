//
// Created by Jason Markham on 2/13/18.
//

#include <Robot.h>
#include "DriveForward.h"

DriveForward::DriveForward(double distanceInches)
        : Command("Drive Forward(" + std::to_string(distanceInches) + "in)", 5.0), distance{distanceInches} {

    Requires(Robot::chassis.get());

}

void DriveForward::Initialize() {
    double amt = distance == 0.0 ? SmartDashboard::GetNumber("fwd", 12.0) : distance;
    Robot::chassis->driveForward_mm(amt);
}

bool DriveForward::IsFinished() {
    return Robot::chassis->driveStraightIsOnTarget();
}

void DriveForward::End() {
    Robot::chassis->stop();
}

DriveForward::DriveForward() : DriveForward(0.0) {

}
