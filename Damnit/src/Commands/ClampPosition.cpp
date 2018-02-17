// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.



#include "ClampPosition.h"
#include "Subsystems/clamp.h"
#include "Robot.h"
double clampStartTime;
bool clampOpen;

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

ClampPosition::ClampPosition(double setpoint, double _open_threshold)
        : Command("Clamp("+std::to_string(setpoint)+")"), m_setpoint(setpoint), open_threshold(_open_threshold) {

        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::clamp.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void ClampPosition::Initialize() {
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZE
    Robot::clamp->Enable();

    if (m_setpoint == -1){  // special code for toggle clamp
    	if (clampOpen)
    		Robot::clamp->SetSetpoint(0);  // close clamp
    	else
    		Robot::clamp->SetSetpoint(152); // open clamp 220 is in oi.cpp also %rod15
    	clampOpen = !clampOpen;
    }
    else{
      Robot::clamp->SetSetpoint(m_setpoint);  // use setpoint
      clampOpen = (m_setpoint > open_threshold);
    }

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZE
    clampStartTime = Timer::GetFPGATimestamp();
    Robot::clamp->SetOutputRange(-1, 1);
}

// Called repeatedly when this Command is scheduled to run
void ClampPosition::Execute() {
//	double currentTime = Timer::GetFPGATimestamp();
//	double elapsed = currentTime - startTime;
//	if (elapsed > 2.0)
//		End();
}

// Make this return true when this Command no longer needs to run execute()
bool ClampPosition::IsFinished() {
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ISFINISHED
	double currentTime = Timer::GetFPGATimestamp();
	double elapsed = currentTime - clampStartTime;
	if (elapsed > 0.5)
		return true;
    return Robot::clamp->OnTarget();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ISFINISHED
}

// Called once after isFinished returns true
void ClampPosition::End() {
	Robot::clamp->SetOutputRange(-0.2, 0.2);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClampPosition::Interrupted() {

}
