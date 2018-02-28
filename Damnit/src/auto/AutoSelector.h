//
// Created by Jason Markham on 2/27/18.
//

#pragma once

#include <string>
#include <Commands/Command.h>
#include <SmartDashboard/SendableChooser.h>

struct AutoSelector {
    AutoSelector();

    frc::Command* getCommand();


private:
    bool messageIsValid(const std::string& msg);

    SendableChooser<std::string> chooser{};

};


