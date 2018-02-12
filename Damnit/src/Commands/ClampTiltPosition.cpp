// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.



#include "ClampTiltPosition.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

ClampTiltPosition::ClampTiltPosition(double setpoint): Command() {
    m_setpoint = setpoint;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::clampTilt.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    holdPower = 0.2;  // this is 20% of max power
    maxPower = 1.0;
    // with 1 5000 rpm motor and 71:1 gearbox and a 7 cpr encoder on motor
    // maxVelocity is about 5000/60/71 = 14000rpm/60/245 = 1.1 rps * 1024 counts/sec.
	maxVelocity = 500;  // encoder counts per second (about 1/3 rev/sec)
	targetVelocity = 250; // maxVelocity / 2;
	velocityP = 0.001;
	velocityFF = 1 / maxVelocity;
	acceleration = 400;  // accel to 300 counts/sec in one second
	deceleration = 400;
	PIDband = 20;  // switch to PID when within this band.
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void ClampTiltPosition::Initialize() {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZE
    Robot::clampTilt->Enable();
    Robot::clampTilt->SetSetpoint(m_setpoint);

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZE
    // the following is for ramp control and stalled shutoff
    startTime = Timer::GetFPGATimestamp();
    prevTime = startTime;
    prevPosition = Robot::clampTilt->GetPosition();
	velocityControl = false;  // assume in PID mode
}

// Called repeatedly when this Command is scheduled to run
void ClampTiltPosition::Execute() {
	double currentTime = Timer::GetFPGATimestamp();
	double elapsedTime = currentTime - startTime;

	if (elapsedTime > 5.0)  // move must end in 5 seconds
		End();  // exit to low power.

	// now determine if we are in velocity or position control.
	double currentPosition = Robot::clampTilt->GetPosition();
	double distanceToTarget = m_setpoint - currentPosition;
	SmartDashboard::PutNumber("Lower", currentPosition);

	if (fabs(distanceToTarget) < PIDband) {
		if (velocityControl) {
			velocityControl = false;
			Robot::clampTilt->Enable();  // go to PID distance control
		}
	} else {
		if (!velocityControl) {
			velocityControl = true;
			Robot::clampTilt->Disable();  // go to velocity control
		}
	}


	// if in velocityControl do things, otherwise let PID do things.
	if (velocityControl) {
		// see if we should be accelerating
		double desiredVelocity = acceleration * (elapsedTime);
		if (desiredVelocity > targetVelocity)
			desiredVelocity = targetVelocity;   //should be done accelerating

		// now estimate distance required to decelerate to target
		float distanceToStop = desiredVelocity * desiredVelocity / (2 * deceleration);
		float remainingDistance = fabs(distanceToTarget);
		if (distanceToStop >= remainingDistance)
			desiredVelocity = sqrt(2 * remainingDistance * deceleration);

		// make a minimum velocity to get things moving and keep moving to target
		if (desiredVelocity < (targetVelocity / 5)) // make them minimum velocity 1/5 target
			desiredVelocity = targetVelocity / 5;
		// get the direction set.
		if (distanceToTarget < 0)
			desiredVelocity *= -1; // go in negative direction.

		double currentVelocity = (currentPosition - prevPosition) / (currentTime - prevTime); //(Robot::upperTilt->GetRate();
		double velocityError = desiredVelocity - currentVelocity;
		;
		double drivePower = velocityFF * desiredVelocity + // this is the feedforward component
				velocityP * velocityError;  // the is the proportional component

		if (drivePower > maxPower)
			drivePower = maxPower;
		else if (drivePower < -maxPower)
			drivePower = -maxPower;
		Robot::clampTilt->motor->Set(drivePower);

		printf("et,sp,cp,dt,vc,cv,tv,d2s,dv,dp %5.2f %3.0f %3.0f %3.0f %d %3.0f %3.0f %3.0f %3.0f %4.2f \n",
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



	}
	prevPosition = currentPosition;
	prevTime = currentTime;


}

// Make this return true when this Command no longer needs to run execute()
bool ClampTiltPosition::IsFinished() {
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ISFINISHED
    return Robot::clampTilt->OnTarget();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ISFINISHED
}

// Called once after isFinished returns true
void ClampTiltPosition::End() {
	Robot::clampTilt->SetOutputRange(-holdPower,holdPower);  // hold at low power

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClampTiltPosition::Interrupted() {
  End();
}