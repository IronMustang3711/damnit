//
// Created by Jason Markham on 2/20/18.
//

#ifndef DAMNIT_SCALEAUTOS_H
#define DAMNIT_SCALEAUTOS_H


#include <Commands/CommandGroup.h>
#include "MotionProfileExecutors.h"

class ScaleAuto : public frc::CommandGroup {
public:
    explicit ScaleAuto(MotionProfileExecutor* exec);
};

class RRScaleAuto : public ScaleAuto {
public:
    inline RRScaleAuto() : ScaleAuto(new RRScale()) {}

};

#endif //DAMNIT_SCALEAUTOS_H
