// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.



#include "BucketTiltPosition.h"
#include "Robot.h"
struct{
	float armPosition;
	float bucketPosition;
} gearing[6] = {{0,-25},
		{130,-25},
		{150,-5}, // 150,5
		{230,25},   //{200,30},
		{300,50},  //{300,80},
		{400,130}};

double bucketSetpoint;

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

BucketTiltPosition::BucketTiltPosition(double setpoint): Command("bucket tilt("+std::to_string(setpoint)+")") {
    m_setpoint = setpoint;
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::bucket.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    holdPower = 0.3;  // this is 20% of max power
    maxPower = 1.0;
    // with 1 14000rmp motor and 245:1 gearbox and a 1024 cpr encoder
    // maxVelocity is about 14000rpm/60/245 = 1 rps * 1024 counts/sec.
	maxVelocity = 2500;  // 1680 ppr 105rpm / 60
	velocityP = 0.001;
	velocityFF = 1 / maxVelocity;
	targetVelocity = 1800; // 1/2 speed
	acceleration = 600;  //1500;  // accel to 300 counts/sec in one second
	deceleration = 600; // 1500;
	PIDband = 25;  // switch to PID when within this band.
    elapsedTime = 0;
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void BucketTiltPosition::Initialize() {
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZE
	Robot::bucket->Enable();
	Robot::bucket->SetOutputRange(-maxPower, maxPower);  // hold at low power
	startTime = Timer::GetFPGATimestamp();
	prevTime = startTime;
	prevPosition = Robot::bucket->GetPosition();
	velocityControl = false;

	bucketSetpoint = m_setpoint;

	if (m_setpoint == 200) { // special autodump code
		if (Robot::upperTilt->GetPosition() > 250) // are we at scale?
			bucketSetpoint = 210; //Robot::bucket->SetSetpoint(210); // dump to scale
		else
			bucketSetpoint = 80; //Robot::bucket->SetSetpoint(80); // dump to switch
	}
	if ((m_setpoint != 100) &&  // not gearing position to arm angle
			(fabs(bucketSetpoint - prevPosition) > PIDband)) {
		// if we are far from target, start with velocity control
		velocityControl = true;
		Robot::bucket->Disable();  // go to velocity control

	}
	Robot::bucket->SetSetpoint(bucketSetpoint);  // normal setpoint
}


// Called repeatedly when this Command is scheduled to run
void BucketTiltPosition::Execute() {
	double currentPosition = Robot::bucket->GetPosition();
	double currentTime = Timer::GetFPGATimestamp();
	elapsedTime = currentTime - startTime;

	if (m_setpoint == 100) {  // this is the special upper arm following code
		double bucketSetpoint;
		double upperPosition = Robot::upperTilt->GetPosition();
		int index = 0;

		for (int i = 5; i > 0; i--) {
			if (upperPosition > gearing[i].armPosition) {
				index = i;
				break;
			}
		}

		if (index > 4)
			bucketSetpoint = gearing[5].bucketPosition; // end of gearing table
		else if (index > 0)  // lineally interpolate
			bucketSetpoint = gearing[index].bucketPosition
					+ (upperPosition - gearing[index].armPosition)
							* (gearing[index + 1].bucketPosition
									- gearing[index].bucketPosition)
							/ (gearing[index + 1].armPosition
									- gearing[index].armPosition);
		else
			bucketSetpoint = gearing[0].bucketPosition; // start at beginning of gearing table

	    Robot::bucket->SetSetpoint(bucketSetpoint);
//		SmartDashboard::PutNumber("Index", index);
//		SmartDashboard::PutNumber("Upper", upperPosition);
//		SmartDashboard::PutNumber("bucketSetpoint", bucketSetpoint);
	}
	else {
		// now determine if we are in velocity or position control.
		double currentPosition = Robot::bucket->GetPosition();
		double distanceToTarget = bucketSetpoint - currentPosition;
		SmartDashboard::PutNumber("Upper", currentPosition);

		if (velocityControl &&                        // are we controlling velocity?
				fabs(distanceToTarget) < PIDband) {  // are we near target?
			velocityControl = false;
			Robot::bucket->Enable();  // go to PID distance control
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

			double currentVelocity = (currentPosition - prevPosition) / (currentTime - prevTime);
			double velocityError = desiredVelocity - currentVelocity;

			double drivePower = velocityFF * desiredVelocity + // this is the feedforward component
					velocityP * velocityError;  // the is the proportional component

			if (drivePower > maxPower)
				drivePower = maxPower;
			else if (drivePower < -maxPower)
				drivePower = -maxPower;
			Robot::bucket->bucketMotor->Set(drivePower);
		}
		prevPosition = currentPosition;
		prevTime = currentTime;

	}
	SmartDashboard::PutNumber("Bucket",currentPosition);
}

// Make this return true when this Command no longer needs to run execute()
bool BucketTiltPosition::IsFinished() {
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ISFINISHED
	if (m_setpoint == 100)  // geared to arm position
		return false;

	if (elapsedTime > 2.0)  // move must end in 3 seconds
		return true;

	return Robot::bucket->OnTarget();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ISFINISHED
}

// Called once after isFinished returns true
void BucketTiltPosition::End() {
    if (velocityControl) {
		velocityControl = false;
		Robot::bucket->Enable();  // go to PID distance control
    }
	Robot::bucket->SetOutputRange(-holdPower,holdPower);  // hold at low power
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BucketTiltPosition::Interrupted() {
  End();
}
