//
// Created by Jason Markham on 2/19/18.
//

#ifndef DAMNIT_SWITCHDUMPSEQUENCE_H
#define DAMNIT_SWITCHDUMPSEQUENCE_H

#include <Commands/CommandGroup.h>

class SwitchDumpSequence : public frc::CommandGroup{
public:
    SwitchDumpSequence();

protected:
    void End() override ;

};


#endif //DAMNIT_SWITCHDUMPSEQUENCE_H
