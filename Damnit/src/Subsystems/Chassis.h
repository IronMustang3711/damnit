
#pragma once

#include <Commands/Subsystem.h>
#include <WPILib.h>
#include <ctre/Phoenix.h>

namespace chassis_config {
    struct Config {
        double rotation_correction = -0.1;
    };

    constexpr Config COMPETITION_CONFIG{};
    constexpr Config PROTO_CONFIG{0.0};

    const Config &getConfig();

};

class Chassis : public frc::Subsystem {
private:

    std::shared_ptr<WPI_TalonSRX> leftFront;
    std::shared_ptr<WPI_TalonSRX> leftRear;
    std::shared_ptr<frc::SpeedControllerGroup> leftSide;
    std::shared_ptr<WPI_TalonSRX> rightFront;
    std::shared_ptr<WPI_TalonSRX> rightRear1;
    std::shared_ptr<frc::SpeedControllerGroup> rightSide;
    std::shared_ptr<frc::DifferentialDrive> differentialDrive;

    bool reversed = false;

    double rotation_correction;

protected:
    explicit Chassis(double rotation_correction);

public:
    Chassis();

    void InitDefaultCommand() override;

    void Periodic() override;


    void TeleopDrive(std::shared_ptr<Joystick> stickPosition);

    void ArcadeDrive(double fwd, double rotate);

    void curvatureDrive(double fwd, double rotate, bool quickTurn);

    void mm_driveForward_init();

    void mm_Periodic(double distanceInches);

    bool driveStraightIsOnTarget();

    void resetEncoders();

    void prepareForAutonomous();

    void prepareForTeleop();

    void enableInductiveBreaking(bool enable);

    void stop();

    void testPeriodic();

    void toggleDirection();


private:
    void disableMotorSafety();

    void enableMotorSafety();

    double VlPrev = 0;
    double VrPrev = 0;


};

