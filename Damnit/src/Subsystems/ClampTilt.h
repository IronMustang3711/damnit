#pragma once

#include <memory>
#include <Commands/PIDSubsystem.h>
#include <SpeedController.h>
#include <Encoder.h>


class ClampTilt : public frc::PIDSubsystem {
public:
    std::shared_ptr<frc::SpeedController> motor;
    std::shared_ptr<frc::Encoder> encoder;

    ClampTilt();

    double ReturnPIDInput() override;

    void UsePIDOutput(double output) override;

    void reset();
};
