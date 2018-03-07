// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.



#include "UpperTiltPosition.h"
#include "Robot.h"
#include <Commands/Command.h>


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

UpperTiltPosition::UpperTiltPosition(double setpoint) : frc::Command("Upper Tilt(" + std::to_string(setpoint) + ")") {
	elapsedTime = 0;
    m_setpoint = setpoint;
    // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    Requires(Robot::upperTilt.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES

    holdPower = 0.5;  // this is 20% of max power
    maxPower = 1.0;
    // with 1 14000rmp motor and 245:1 gearbox and a 1024 cpr encoder
    // maxVelocity is about 14000rpm/60/245 = 1 rps * 1024 counts/sec.
    maxVelocity = 800;  // 1024ppr 15000/250 rpm /60
    velocityP = 0.002;
    velocityFF = 1 / maxVelocity;
    acceleration = 600;  // accel to 300 counts/sec in one second
    deceleration = 600;
    PIDband = 15;  // switch to PID when within this band.

}
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void UpperTiltPosition::Initialize() {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZE
    Robot::upperTilt->Enable();
    Robot::upperTilt->SetSetpoint(m_setpoint);
    Robot::upperTilt->SetOutputRange(-maxPower, maxPower);  // hold at low power

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZE
    startTime = Timer::GetFPGATimestamp();
    prevTime = startTime;
    prevPosition = Robot::upperTilt->GetPosition();

    // if we are far from target, start with velocity control
    if (fabs(m_setpoint - prevPosition) < PIDband) {
        velocityControl = false;
        Robot::upperTilt->Enable();  // go to PID distance control
    } else {
        velocityControl = true;
        Robot::upperTilt->Disable();  // go to velocity control
    }

    // if going down, select slower velocity.
    if (m_setpoint > prevPosition)
        targetVelocity = 400; // going up
    else
        targetVelocity = 200; // going down;


}

// Called repeatedly when this Command is scheduled to run
void UpperTiltPosition::Execute() {
    double currentTime = Timer::GetFPGATimestamp();
    elapsedTime = currentTime - startTime;

    if (elapsedTime > 3.0) { // move must end in 3 seconds
        velocityControl = false;
        Robot::upperTilt->Enable();  // go to PID distance control
    }

    // now determine if we are in velocity or position control.
    double currentPosition = Robot::upperTilt->GetPosition();
    double distanceToTarget = m_setpoint - currentPosition;
    //SmartDashboard::PutNumber("Upper", currentPosition);

    if (velocityControl &&                        // are we controlling velocity?
        fabs(distanceToTarget) < PIDband) {  // are we near target?
        velocityControl = false;
        Robot::upperTilt->Enable();  // go to PID distance control
    }

    // if in velocityControl do things, otherwise let PID do things.
    if (velocityControl) {
        // see if we should be accelerating
        double desiredVelocity = acceleration * (elapsedTime);
        if (desiredVelocity > targetVelocity)
            desiredVelocity = targetVelocity;   //should be done accelerating

        // now estimate distance required to decelerate to target
        double distanceToStop = desiredVelocity * desiredVelocity / (2 * deceleration);
        double remainingDistance = fabs(distanceToTarget);
        if (distanceToStop >= remainingDistance)
            desiredVelocity = sqrt(2 * remainingDistance * deceleration);

        // make a minimum velocity to get things moving and keep moving to target
        if (desiredVelocity < (targetVelocity / 5)) // make them minimum velocity 1/5 target
            desiredVelocity = targetVelocity / 5;
        // get the direction set.
        if (distanceToTarget < 0)
            desiredVelocity *= -1; // go in negative direction.

        double currentVelocity =
                (currentPosition - prevPosition) / (currentTime - prevTime); //(Robot::upperTilt->GetRate();
        double velocityError = desiredVelocity - currentVelocity;

        double drivePower = velocityFF * desiredVelocity + // this is the feedforward component
                            velocityP * velocityError;  // the is the proportional component

        if (drivePower > maxPower)
            drivePower = maxPower;
        else if (drivePower < -maxPower)
            drivePower = -maxPower;
        Robot::upperTilt->upperMotor->Set(drivePower);

        /*	printf("et,sp,cp,dt,vc,cv,tv,d2s,dv,dp %5.2f %3.0f %3.0f %3.0f %d %3.0f %3.0f %3.0f %3.0f %4.2f \n",
            elapsedTime,
            m_setpoint,
            currentPosition,
            distanceToTarget,
            velocityControl,
            currentVelocity,
            targetVelocity,
            distanceToStop,
            desiredVelocity,
            drivePower);
    */

    }
    prevPosition = currentPosition;
    prevTime = currentTime;

}

// Make this return true when this Command no longer needs to run execute()
bool UpperTiltPosition::IsFinished() {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ISFINISHED
    if (elapsedTime > 3.0)
        return true;
    return Robot::upperTilt->OnTarget();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ISFINISHED
}

// Called once after isFinished returns true
void UpperTiltPosition::End() {
    Robot::upperTilt->SetOutputRange(-holdPower, holdPower);  // hold at low power

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void UpperTiltPosition::Interrupted() {
    End();
}

const upper_tilt::Config &upper_tilt::getConfig() {
    return Robot::isCompetitionRobot ? COMPETITION_CONFIG : PROTO_CONFIG;
}

UpperTiltToSwitch::UpperTiltToSwitch()
        : UpperTiltPosition(upper_tilt::getConfig().switch_setpoint) {}

UpperTiltToScale::UpperTiltToScale()
        : UpperTiltPosition(upper_tilt::getConfig().scale_setpoint) {}

UpperTiltToWinch::UpperTiltToWinch()
        : UpperTiltPosition(upper_tilt::getConfig().winch_setpoint) {}

UpperTiltToHome::UpperTiltToHome()
        : UpperTiltPosition(0) {}
