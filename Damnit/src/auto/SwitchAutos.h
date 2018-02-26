//
// Created by Jason Markham on 2/20/18.
//

#ifndef DAMNIT_SWITCHAUTOS_H
#define DAMNIT_SWITCHAUTOS_H


#include <Commands/CommandGroup.h>


class MotionProfileExecutor;
class SwitchAuto : public frc::CommandGroup {

   // MotionProfileExecutor* mp;

public:
    explicit SwitchAuto(MotionProfileExecutor* exec);

};


class RRSwitchAuto : public SwitchAuto {
public:
     RRSwitchAuto();
};

class CRSwitchAuto : public SwitchAuto {
public:
     CRSwitchAuto();
};
class CLSwitchAuto : public SwitchAuto {
public:
    CLSwitchAuto();
};
class LLSwitchAuto : public SwitchAuto {
public:
    LLSwitchAuto();;
};



#endif //DAMNIT_SWITCHAUTOS_H
