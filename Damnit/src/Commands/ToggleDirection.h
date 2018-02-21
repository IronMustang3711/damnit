//
// Created by Jason Markham on 2/16/18.
//

#ifndef DAMNIT_TOGGLEDIRECTION_H
#define DAMNIT_TOGGLEDIRECTION_H


#include <Commands/InstantCommand.h>

class ToggleDirection : public frc::InstantCommand {
public:
    ToggleDirection();

protected:
    void Initialize() override;

};


#endif //DAMNIT_TOGGLEDIRECTION_H
