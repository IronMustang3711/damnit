#pragma once

#include <memory>
#include <Commands/PIDSubsystem.h>
#include <SpeedController.h>
#include <Encoder.h>


class UpperTilt : public frc::PIDSubsystem {
public:
    std::shared_ptr<frc::SpeedController> upperMotor;
    std::shared_ptr<frc::Encoder> upperEncoder;

    UpperTilt();

    double ReturnPIDInput() override;

    void UsePIDOutput(double output) override;

    void reset();

    void Periodic() override;
};

