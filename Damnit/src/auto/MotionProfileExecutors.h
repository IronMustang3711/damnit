//
// Created by Jason Markham on 2/19/18.
//

#ifndef DAMNIT_MOTIONPROFILEEXECUTORS_H
#define DAMNIT_MOTIONPROFILEEXECUTORS_H

#include "MotionProfileExecutor.h"

class CRSwitch : public MotionProfileExecutor {
public:
    CRSwitch();
};
class CRScale : public  MotionProfileExecutor {
public:
    CRScale();
};

class Straight_10ft : public  MotionProfileExecutor {
public:
    Straight_10ft();
};
class RRScale : public  MotionProfileExecutor {
public:
    RRScale();
};
class RRSwitch : public  MotionProfileExecutor {
public:
    RRSwitch();
};



#endif //DAMNIT_MOTIONPROFILEEXECUTORS_H
