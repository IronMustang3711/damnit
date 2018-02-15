//
// Created by Jason Markham on 2/15/18.
//

#pragma once

#include <Commands/Command.h>

class DontDoAnything : public frc::Command {
public:
    DontDoAnything();

protected:
    void Initialize() override;
    bool IsFinished() override ;
};