//
// Created by Jason Markham on 2/15/18.
//

#ifndef DAMNIT_AUTOBUILDER_H
#define DAMNIT_AUTOBUILDER_H


#include <Commands/Command.h>
#include <Commands/InstantCommand.h>

class AutoBuilder : public frc::InstantCommand{
public:
    AutoBuilder();

protected:
    void Initialize() override ;

};


#endif //DAMNIT_AUTOBUILDER_H
