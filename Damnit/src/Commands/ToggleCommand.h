//
// Created by Jason Markham on 2/20/18.
//

#pragma once
#include <Commands/ConditionalCommand.h>

class ToggleCommand  : public frc::ConditionalCommand{
public:
    ToggleCommand(const llvm::Twine &name, Command *onTrue, Command *onFalse);

protected:
    bool Condition() override;

private:
    bool toggle = true;

};


