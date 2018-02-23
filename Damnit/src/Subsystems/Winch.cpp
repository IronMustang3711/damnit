#include "Winch.h"
#include "RobotMap.h"

Winch::Winch() : Subsystem("Winch") {
    winchMotor = RobotMap::winchMotor;
}

void Winch::driveWinch(double speed) {
    winchMotor->Set(speed);
}
