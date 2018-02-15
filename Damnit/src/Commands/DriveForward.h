//
// Created by Jason Markham on 2/13/18.
//

#pragma once


#include <Commands/Command.h>
#include <Commands/TimedCommand.h>
#include <PIDSource.h>
#include <PIDOutput.h>
#include <PIDController.h>


class DriveForward : public frc::Command {
public:
    explicit DriveForward(double distanceInches);

    DriveForward();

protected:
    void Initialize() override;
    void Execute() override;

    bool IsFinished() override;

    void End() override;


private:
    double distance;
    int onTargetCount = 0;
  //  LinearDigitalFilter errFilter;

};


class DumbDriveForward : public frc::TimedCommand {
public:
    explicit DumbDriveForward(double time = 2.0);

protected:
    void Execute() override;

    void End() override;


};


class DriveForwardGyroEncoder : public frc::Command,
                                public frc::PIDSource,
                                public frc::PIDOutput {
public:
    explicit DriveForwardGyroEncoder(double distanceInches = 48.0, double timeout = 0.0);

    double encoderValue();


// PIDOutput interface
    void PIDWrite(double output) override;

    // PIDSource interface
    double PIDGet() override;


protected:
    void Initialize() override;

    void Execute() override;

    void End() override;

    bool IsFinished() override;

private:
    PIDController pid;
    double targetTicks = 0;
    double initialHeading = 0;
    double initialEncoder = 0;


};




