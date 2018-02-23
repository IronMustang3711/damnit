
#include <PIDController.h>
#include <Robot.h>

#include "Clamp.h"
#include "RobotMap.h"

Clamp::Clamp() : PIDSubsystem("Clamp", 0.02, 0.0, 0.0) {
    SetAbsoluteTolerance(5.0);
    GetPIDController()->SetContinuous(false);

    GetPIDController()->SetName("Clamp PID Controller");

    clampMotor = RobotMap::clampClampMotor;
    clampEncoder = RobotMap::clampClampEncoder;

}

double Clamp::ReturnPIDInput() {
    return clampEncoder->PIDGet();
}

void Clamp::UsePIDOutput(double output) {
    clampMotor->PIDWrite(output);
}

void Clamp::reset() {
    clampMotor->StopMotor();
    clampEncoder.reset();
}
