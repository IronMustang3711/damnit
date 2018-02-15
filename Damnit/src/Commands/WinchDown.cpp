#include "WinchDown.h"
#include "Robot.h"
WinchDown::WinchDown() : frc::Command("Winch Down") {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(Robot::winch.get());

}

// Called just before this Command runs the first time
void WinchDown::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void WinchDown::Execute() {
  Robot::winch->driveWinch(-0.5);

}

// Make this return true when this Command no longer needs to run execute()
bool WinchDown::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void WinchDown::End() {
	  Robot::winch->driveWinch(0);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WinchDown::Interrupted() {
  End();
}
