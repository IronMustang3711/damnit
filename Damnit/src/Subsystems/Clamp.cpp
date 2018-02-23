
#include <PIDController.h>
#include <Robot.h>
#include <ReaderBoard.h>

#include "Clamp.h"
#include "RobotMap.h"

Clamp::Clamp() : PIDSubsystem("Clamp", 0.02, 0.0, 0.0) {

    if(!Robot::isCompetitionRobot){
        open_setpoint = PROTO_OPEN_SETPOINT;
        close_setpoint = PROTO_CLOSE_SETPOINT;
    }

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

void Clamp::open() {
    SetOutputRange(-MAX_OUT, MAX_OUT);
    SetSetpoint(open_setpoint);
    ReaderBoard::getInstance().reportClampOpen();


    Enable();

}

void Clamp::close() {
    SetOutputRange(-MAX_OUT, MAX_OUT);
    SetSetpoint(close_setpoint);
    ReaderBoard::getInstance().reportClampClose();

    Enable();
}
