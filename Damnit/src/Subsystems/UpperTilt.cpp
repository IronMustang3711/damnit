
#include <PIDController.h>

#include "UpperTilt.h"
#include "RobotMap.h"

UpperTilt::UpperTilt() : PIDSubsystem("UpperTilt", 0.01, 0.0, 0.0, 0.1, 0.01) {
    SetAbsoluteTolerance(5.0);
    GetPIDController()->SetContinuous(false);

    GetPIDController()->SetName("Upper Tilt PID Controller");
    upperMotor = RobotMap::upperTiltUpperMotor;
    upperEncoder = RobotMap::upperTiltUpperEncoder;

}

double UpperTilt::ReturnPIDInput() {
    return upperEncoder->PIDGet();
}

void UpperTilt::UsePIDOutput(double output) {
    upperMotor->PIDWrite(output);
}


void UpperTilt::reset() {
    upperEncoder->Reset();
}

void UpperTilt::Periodic() {
    SmartDashboard::PutString("upper_tilt:pid?", GetPIDController()->IsEnabled() ? "yes" : "no");
}
