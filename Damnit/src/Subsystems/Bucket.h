

#pragma once

#include <Commands/PIDSubsystem.h>
#include <SpeedController.h>
#include <Encoder.h>

class Bucket : public frc::PIDSubsystem {
public:
    std::shared_ptr<frc::SpeedController> bucketMotor;
    std::shared_ptr<frc::Encoder> bucketEncoder;

    Bucket();

    double ReturnPIDInput() override;

    void UsePIDOutput(double output) override;

    void reset();
};
