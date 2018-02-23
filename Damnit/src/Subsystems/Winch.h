#pragma once

#include <memory>
#include <Commands/Subsystem.h>
#include <SpeedController.h>

class Winch : public Subsystem {
private:
    std::shared_ptr<frc::SpeedController> winchMotor;

public:
    Winch();

    void driveWinch(double speed);
};
