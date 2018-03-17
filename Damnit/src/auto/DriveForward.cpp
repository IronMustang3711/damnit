//
// Created by Jason Markham on 2/13/18.
//

#include <Robot.h>
#include "DriveForward.h"

DriveForward::DriveForward(double distanceInches,double timeout)
        : Command("Drive Forward(mm)" /*+ std::to_string(distanceInches) + "in)"*/, timeout), distance{distanceInches} {

    Requires(Robot::chassis.get());


}

void DriveForward::Initialize() {
    //double amt = distance == 0.0 ? SmartDashboard::GetNumber("fwd", 12.0) : distance;
   // Robot::chassis->disableMotorSafety();
    Robot::chassis->prepareForAutonomous();
    Robot::chassis->mm_driveForward_init();
    onTargetCount = 0;
}

bool DriveForward::IsFinished() {

    if (Robot::chassis->driveStraightIsOnTarget()) {
        onTargetCount++;
    }
    return onTargetCount >= 10 || IsTimedOut();
}

void DriveForward::End() {
    Robot::chassis->stop();


}

void DriveForward::Execute() {
    Robot::chassis->mm_Periodic(distance);
}



/************* DriveForwardGyroEncoder ***************/

DriveForwardGyroEncoder::DriveForwardGyroEncoder(double distanceInches, double timeout)
        : Command("Drive Forward(Encoder/Gyro): ",timeout) /*+ std::to_string(distanceInches), timeout)*/, pid{
	/*P*/     0.0007,
        /*I*/      0.0,
        /*D*/      0.0,
        /*F*/      0.01,
        /*source*/ this,
        /*output*/ this,
        /*update rate*/ 0.01},
          targetTicks{75.0 * distanceInches} {

    Requires(Robot::chassis.get());
    SetPIDSourceType(PIDSourceType::kDisplacement);
}

double DriveForwardGyroEncoder::encoderValue() {
    return (RobotMap::chassisLeftFront->GetSelectedSensorPosition(0)
            + RobotMap::chassisRightFront->GetSelectedSensorPosition(0)) / 2.0;
}

void DriveForwardGyroEncoder::PIDWrite(double output) {
    double angleCorrection = (-1 / 30.0) * (RobotMap::ahrs->GetAngle() - initialHeading);
    if(angleCorrection > 0.2) angleCorrection = 0.2;
    if(angleCorrection < -0.2) angleCorrection = -0.2;
    //llvm::outs() << "angle correction: " << angleCorrection << '\n';
    SmartDashboard::PutNumber("AngleCorrection", angleCorrection);
    Robot::chassis->ArcadeDrive(output, angleCorrection);//curvatureDrive(output, angleCorrection, false);
}

double DriveForwardGyroEncoder::PIDGet() {
    return encoderValue() - initialEncoder;
}

void DriveForwardGyroEncoder::Initialize() {
	Robot::chassis->prepareForAutonomous();
    Robot::chassis->resetEncoders();
    RobotMap::ahrs->Reset();
    pid.Reset();
    initialEncoder = RobotMap::chassisLeftFront->GetSelectedSensorPosition(0);

    pid.SetInputRange(0, targetTicks);
    pid.SetOutputRange(-0.1, 0.3);
    pid.SetAbsoluteTolerance(0.05);
    pid.SetSetpoint(targetTicks);
    initialHeading = RobotMap::ahrs->GetAngle(); //Robot::chassis->getHeading();

    pid.Enable();
}

void DriveForwardGyroEncoder::Execute() {
    SmartDashboard::PutNumber("DriveStraight_Err", pid.GetError());
}

void DriveForwardGyroEncoder::End() {
	if(IsTimedOut()) DriverStation::ReportError("DriveStraight(ge) timed out!");
    pid.Disable();
    Robot::chassis->stop();
}

bool DriveForwardGyroEncoder::IsFinished() {
    return IsTimedOut() || pid.OnTarget() || (pid.GetError() < -50.0);
}

/************* DumbDriveForward ***************/
DumbDriveForward::DumbDriveForward(double time) : TimedCommand("Drive Forward(timed)", // + std::to_string(time) + ")",
                                                               time) {
    Requires(Robot::chassis.get());
}


void DumbDriveForward::Execute() {
    Robot::chassis->curvatureDrive(-0.4, 0.0, false);
}

void DumbDriveForward::End() {
    Command::End();
}