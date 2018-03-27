//
// Created by Jason Markham on 2/19/18.
//

#include <WPILib.h>
#include <ctre/Phoenix.h>
#include "profile.h"

#pragma once
class MotionProfileExecutor : public frc::Command{
public:
    //TODO: remove timeout parameter - calculate from profile
    MotionProfileExecutor(const llvm::Twine& name, double timeout,const std::vector<mp::Prof>& profs);


    double getPercentCompleted();
    double getNominalDuration();

protected:
    void Initialize() override;

    void Execute() override;

    bool IsFinished() override;

    void End() override;

    void Interrupted() override ;

    void update();

    static constexpr int CLOSED_LOOP_SLOT = 0;
    static constexpr int PRIMARY_PID_IDX = 0;
    static constexpr int TIMEOUT = 10;

    void fill();

private:
    std::unique_ptr<frc::Notifier> notifier;
    WPI_TalonSRX *left;
    WPI_TalonSRX *right;

    const std::vector<mp::Prof>& profiles;

    size_t fillIndex = 0;
    bool finished = false;

};


