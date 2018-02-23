#pragma once

#include <memory>
#include <Commands/PIDSubsystem.h>
#include <SpeedController.h>
#include <Encoder.h>


class Clamp : public frc::PIDSubsystem {
public:
    std::shared_ptr<frc::SpeedController> clampMotor;
    std::shared_ptr<frc::Encoder> clampEncoder;

    Clamp();

    double ReturnPIDInput() override;

    void UsePIDOutput(double output) override;

    void reset();
};

