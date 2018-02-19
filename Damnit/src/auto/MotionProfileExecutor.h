//
// Created by Jason Markham on 2/19/18.
//

#include <WPILib.h>
#include <ctre/Phoenix.h>
#include "profile.h"

#pragma once
class MotionProfileExecutor : public frc::Command{
public:
    MotionProfileExecutor(const llvm::Twine& name, double timeout,const std::vector<mp::Prof>& profs);


protected:
    void Initialize() override;

    void Execute() override;

    bool IsFinished() override;

    void End() override;

    void update();

    typedef std::vector<mp::Prof>::const_iterator ProfIter;
    static constexpr int SLOT = 0;
    static constexpr int TIMEOUT = 10;

    void fill();

private:
    std::unique_ptr<frc::Notifier> notifier;
    WPI_TalonSRX *left;
    WPI_TalonSRX *right;

    const std::vector<mp::Prof>& profiles;

    size_t fillIndex = 0;

};


