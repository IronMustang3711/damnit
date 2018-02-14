//
// Created by Jason Markham on 2/13/18.
//

#ifndef DAMNIT_SPIN_H
#define DAMNIT_SPIN_H


#include <Commands/TimedCommand.h>

class Spin : public frc::TimedCommand {

    void Execute() override;

public:
    Spin();
};


#endif //DAMNIT_SPIN_H
