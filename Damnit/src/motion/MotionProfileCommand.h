/*
 * MotionProfileCommand.h
 *
 *  Created on: Feb 14, 2018
 *      Author: jason
 */

#pragma once

#include <WPILib.h>
#include <ctre/Phoenix.h>
#include "profile.h"

class MotionProfileCommand : public frc::Command {
public:
    MotionProfileCommand();

    static constexpr int SLOT = 0;
    static constexpr int TIMEOUT = 10;

protected:
    void Initialize() override;

    void Execute() override;

    bool IsFinished() override;

    void End() override;

    void update();

    typedef decltype(mp::PROFS)::const_iterator ProfIter;

    void fill(ProfIter stopAt = mp::PROFS.cend());

private:
    std::unique_ptr<Notifier> notifier;
    WPI_TalonSRX *left;
    WPI_TalonSRX *right;

    ProfIter it;
};

