//
// Created by Jason Markham on 2/19/18.
//

#include "MotionProfileExecutors.h"
#include "CRScale_profile.h"
#include "CRSwitch_profile.h"
#include "DriveStraight_10ft_profile.h"
#include "RRScale_profile.h"
#include "RRSwitch_profile.h"

CRSwitch::CRSwitch() : MotionProfileExecutor("Center->Right Switch",6.0,mp::CRSwitch) {

}

CRScale::CRScale(): MotionProfileExecutor("Center->Right Scale",6.0,mp::CRScale)  {

}

Straight_10ft::Straight_10ft() : MotionProfileExecutor("straight 10ft",7.0,mp::DriveStraight_10ft) {

}

RRScale::RRScale() : MotionProfileExecutor("Right->Right Scale", 12.0,mp::RRScale) {

}

RRSwitch::RRSwitch() : MotionProfileExecutor("Right->Right Switch",7.0,mp::RRSwitch) {

}
