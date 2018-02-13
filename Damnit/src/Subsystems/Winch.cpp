#include "Winch.h"
#include "RobotMap.h"

Winch::Winch() : Subsystem("Winch") {
    winchMotor = RobotMap::winchMotor;

}

void Winch::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void Winch::driveWinch(double speed){
	winchMotor->Set(speed);
}
