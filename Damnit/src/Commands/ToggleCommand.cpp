//
// Created by Jason Markham on 2/20/18.
//

#include "ToggleCommand.h"

ToggleCommand::ToggleCommand(const llvm::Twine &name, Command *onTrue, Command *onFalse)
        : ConditionalCommand(name,onTrue,onFalse) {}

bool ToggleCommand::Condition() {
    bool result = toggle;
    toggle = !toggle;
    return result;

}
