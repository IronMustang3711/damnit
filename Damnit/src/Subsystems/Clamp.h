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

    void open();

    void close();

protected:
    void Periodic() override ;


private:
    double open_setpoint = 140.0;
    double close_setpoint = 0.0;

    static constexpr double PROTO_OPEN_SETPOINT = 140.0;
    static constexpr double PROTO_CLOSE_SETPOINT = 0.0;

    static constexpr double MAX_OUT = 0.7;
};

