//
// Created by Jason Markham on 2/23/18.
//

#include "Robot.h"
#include "ReaderBoard.h"
#include "WinchCommands.h"

bool WinchCommand::IsFinished() {
    return false;
}

WinchCommand::WinchCommand(const llvm::Twine& name, double o) : frc::Command(name),output(o) {
    Requires(Robot::winch.get());
}

void WinchCommand::Execute() {
    ReaderBoard::reportWinch(GetName());
    Robot::winch->driveWinch(output);
}

void WinchCommand::End() {
    Robot::winch->driveWinch(0.0);
}



