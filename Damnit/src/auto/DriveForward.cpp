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
    //double amt = distance == 0.0 ? SmartDashboard::GetNumber("fwd", 12.0) : distance;
    Robot::chassis->disableMotorSafety();
    Robot::chassis->mm_driveForward_init();
}

bool DriveForward::IsFinished() {

    if (Robot::chassis->driveStraightIsOnTarget()) {
        onTargetCount++;
    }
    return onTargetCount >= 10;
}

void DriveForward::End() {
    Robot::chassis->stop();
    Robot::chassis->enableMotorSafety();

}

void DriveForward::Execute() {
    Robot::chassis->mm_Periodic(distance);
}

/************* DumbDriveForward ***************/
DumbDriveForward::DumbDriveForward(double time) : TimedCommand("Timed Drive Forward(" + std::to_string(time) + ")",
                                                               time) {
    Requires(Robot::chassis.get());
}


void DumbDriveForward::Execute() {
    Robot::chassis->curvatureDrive(0.2, 0.0, false);
}

void DumbDriveForward::End() {
    Command::End();
}

/************* DriveForwardGyroEncoder ***************/

DriveForwardGyroEncoder::DriveForwardGyroEncoder(double distanceInches, double timeout)
        : Command("Drive Forward(Encoder/Gyro): " + std::to_string(distanceInches), timeout), pid{  /*P*/     0.15,
        /*I*/      0.0,
        /*D*/      0.0,
        /*F*/      0.01,
        /*source*/ this,
        /*output*/ this,
        /*update rate*/ 0.02},
          targetTicks{75.0 * distanceInches} {
    Requires(Robot::chassis.get());
}

double DriveForwardGyroEncoder::encoderValue() {
    return (RobotMap::chassisLeftFront->GetSensorCollection().GetQuadraturePosition()
            + RobotMap::chassisRightFront->GetSensorCollection().GetQuadraturePosition()) / 2.0;
}

void DriveForwardGyroEncoder::PIDWrite(double output) {
    double angleCorrection = (-1 / 45.0) * (RobotMap::ahrs->GetAngle() - initialHeading);
    Robot::chassis->curvatureDrive(output, angleCorrection, false);
}

double DriveForwardGyroEncoder::PIDGet() {
    return encoderValue() - initialEncoder;
}

void DriveForwardGyroEncoder::Initialize() {
    Robot::chassis->resetEncoders();
    initialEncoder = RobotMap::chassisLeftFront->GetSensorCollection().GetQuadraturePosition();
    pid.SetInputRange(0, targetTicks);
    pid.SetOutputRange(-0.3, 0.3);
    pid.SetAbsoluteTolerance(0.1);
    pid.SetSetpoint(targetTicks);
    initialHeading = RobotMap::ahrs->GetAngle(); //Robot::chassis->getHeading();
    pid.Enable();
}

void DriveForwardGyroEncoder::Execute() {
    SmartDashboard::PutNumber("DriveStraight: error", pid.GetError());
}

void DriveForwardGyroEncoder::End() {
    pid.Disable();
    Robot::chassis->stop();
}

bool DriveForwardGyroEncoder::IsFinished() {
    return IsTimedOut() || pid.OnTarget();
}

