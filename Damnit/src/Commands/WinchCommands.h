//
// Created by Jason Markham on 2/23/18.
//

#ifndef DAMNIT_WINCHCOMMANDS_H
#define DAMNIT_WINCHCOMMANDS_H


#include <Commands/Command.h>

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
   inline WinchHold() : WinchCommand("winch hold",0.1){}
};
class WinchDisable : public WinchCommand {
public:
    inline WinchDisable(): WinchCommand("winch disable",0.0){}
};
class WinchUp: public WinchCommand {
public:
    inline WinchUp() : WinchCommand("winch up",0.5){}
};

class WinchDown : public WinchCommand {
public:
    inline WinchDown() : WinchCommand("winch down", -0.5){}
};

#endif //DAMNIT_WINCHCOMMANDS_H
