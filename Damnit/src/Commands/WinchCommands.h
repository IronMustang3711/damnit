//
// Created by Jason Markham on 2/23/18.

#pragma once


#include <Commands/Command.h>
#include <Commands/InstantCommand.h>

class WinchCommand : public frc::Command {
public:
    WinchCommand(const llvm::Twine& name, double output);

protected:
    bool IsFinished() override ;
    void Execute() override ;
    void End() override ;

private:
    double output;

};


class WinchHold : public WinchCommand {
public:
   inline WinchHold() : WinchCommand("winch hold",0.3){}
};


class WinchUp: public WinchCommand {
public:
    inline WinchUp() : WinchCommand("winch up",0.8){}
};

class WinchDown : public WinchCommand {
public:
    inline WinchDown() : WinchCommand("winch down", -0.7){}
};


class WinchDisable : public frc::InstantCommand {
public:
    WinchDisable();

protected:
    void Execute() override;
};
