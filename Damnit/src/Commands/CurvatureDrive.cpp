//
// Created by Jason Markham on 2/13/18.
//

#include <Robot.h>
#include "CurvatureDrive.h"

CurvatureDrive::CurvatureDrive() : Command("Curvature Drive") {
    Requires(Robot::chassis.get());
}

void CurvatureDrive::Initialize() {
    Robot::chassis->prepareForTeleop();
}

void CurvatureDrive::Execute() {
    auto joy = Robot::oi->getDriveJoystick();
    auto fwd = -joy->GetY();
    auto rotate = joy->GetZ();
    auto quick = joy->GetRawButton(1);

    fwd = fwd * fwd * fwd;
    rotate = rotate * rotate * rotate;

    Robot::chassis->curvatureDrive(fwd, rotate, quick);
}

bool CurvatureDrive::IsFinished() {
    return false;
}
