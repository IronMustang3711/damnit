//
// Created by Jason Markham on 2/20/18.
//

#ifndef DAMNIT_SCALEAUTOS_H
#define DAMNIT_SCALEAUTOS_H


#include <Commands/CommandGroup.h>

class MotionProfileExecutor;

class ScaleAuto : public frc::CommandGroup {
public:
    explicit ScaleAuto(MotionProfileExecutor* exec);
};

class RRScaleAuto : public ScaleAuto {
public:
    RRScaleAuto();

};
class LLScaleAuto : public ScaleAuto {
public:
    LLScaleAuto();
};

#endif //DAMNIT_SCALEAUTOS_H
