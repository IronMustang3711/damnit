//
// Created by Jason Markham on 2/15/18.
//

#ifndef DAMNIT_AUTOBUILDER_H
#define DAMNIT_AUTOBUILDER_H


#include <Commands/Command.h>
#include <Commands/InstantCommand.h>
#include "FieldModel.h"

class AutoBuilder : public frc::InstantCommand{
public:
    AutoBuilder();

protected:
    void Initialize() override ;

private:
    Command* centerStartingPoint(TargetLocation switchLocation);
    Command* leftStartingPoint(TargetLocation switchLocation, TargetLocation scaleLocation);
    Command* rightStartingPoint(TargetLocation switchLocation, TargetLocation scaleLocation);

};


#endif //DAMNIT_AUTOBUILDER_H
