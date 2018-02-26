//
// Created by Jason Markham on 2/23/18.
//

#include <Robot.h>
#include "WinchCommands.h"

bool WinchCommand::IsFinished() {
    return false;
}

WinchCommand::WinchCommand(const llvm::Twine& name, double o) : frc::Command(name),output(o) {
    Requires(Robot::winch.get());
}

void WinchCommand::Execute() {
    Robot::winch->driveWinch(output);
}

void WinchCommand::End() {
    Robot::winch->driveWinch(0.0);
}

WinchDisable::WinchDisable() : InstantCommand("disable winch") {

}

void WinchDisable::Execute() {
    Robot::winch->driveWinch(0.0);
}
