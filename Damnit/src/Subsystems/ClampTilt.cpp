
#include <PIDController.h>

#include "ClampTilt.h"
#include "RobotMap.h"

ClampTilt::ClampTilt() : PIDSubsystem("ClampTilt", 0.03, 0.0, 0.0) {
    SetAbsoluteTolerance(5.0);
    GetPIDController()->SetContinuous(false);

    GetPIDController()->SetName("Clamp Tilt PID Controller");

    motor = RobotMap::clampTiltMotor;
    encoder = RobotMap::clampTiltEncoder;
}

double ClampTilt::ReturnPIDInput() {
    return encoder->PIDGet();
}

void ClampTilt::UsePIDOutput(double output) {
    motor->PIDWrite(output);
}

void ClampTilt::reset() {
    motor->StopMotor();
    encoder->Reset();
}
