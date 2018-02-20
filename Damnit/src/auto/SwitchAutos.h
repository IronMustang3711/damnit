//
// Created by Jason Markham on 2/20/18.
//

#ifndef DAMNIT_SWITCHAUTOS_H
#define DAMNIT_SWITCHAUTOS_H


#include <Commands/CommandGroup.h>
#include "MotionProfileExecutor.h"
#include "MotionProfileExecutors.h"


class SwitchAuto : public frc::CommandGroup {

    MotionProfileExecutor* mp;

public:
    explicit SwitchAuto(MotionProfileExecutor* exec);

};


class RRSwitchAuto : public SwitchAuto {
public:
    inline RRSwitchAuto() : SwitchAuto(new RRSwitch()){};
};

class CRSwitchAuto : public SwitchAuto {
public:
    inline CRSwitchAuto() : SwitchAuto(new CRSwitch()){};
};


#endif //DAMNIT_SWITCHAUTOS_H
