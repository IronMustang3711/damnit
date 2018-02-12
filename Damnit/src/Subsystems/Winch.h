#ifndef winch_H
#define winch_H

#include <Commands/Subsystem.h>
#include "WPILib.h"

class Winch : public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<frc::SpeedController> winchMotor;

public:
	Winch();
	void InitDefaultCommand();

	void driveWinch(double speed);
};

#endif  // winch_H
