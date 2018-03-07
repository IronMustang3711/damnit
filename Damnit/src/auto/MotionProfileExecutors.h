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
class CLSwitch : public MotionProfileExecutor {
public:
    CLSwitch();
};
class LFwd : public MotionProfileExecutor {
public:
    LFwd();
};
class LLScale : public MotionProfileExecutor {
public:
    LLScale();
};
class LLSwitch : public MotionProfileExecutor {
public:
    LLSwitch();
};
class RFwd : public MotionProfileExecutor {
public:
    RFwd();
};
class RLScale : public MotionProfileExecutor {
public:
    RLScale();
};


#endif //DAMNIT_MOTIONPROFILEEXECUTORS_H
