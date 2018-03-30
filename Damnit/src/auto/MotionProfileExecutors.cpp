//
// Created by Jason Markham on 2/19/18.
//

#include "MotionProfileExecutors.h"
#include "CRScale_profile.h"
#include "CRSwitch_profile.h"
#include "DriveStraight_10ft_profile.h"
#include "RRScale_profile.h"
#include "RRSwitch_profile.h"
#include "CLScale_profile.h"
#include "CLSwitch_profile.h"
#include "LFwd_profile.h"
#include "LLScale_profile.h"
#include "LLSwitch_profile.h"
#include "RFwd_profile.h"
#include "RLScale_profile.h"
#include "LRScale_profile.h"


CRSwitch::CRSwitch() : MotionProfileExecutor("Center->Right Switch",8.0,mp::CRSwitch) {
}


Straight_10ft::Straight_10ft() : MotionProfileExecutor("straight 10ft",10.0,mp::DriveStraight_10ft) {

}

RRScale::RRScale() : MotionProfileExecutor("Right->Right Scale", 12.0,mp::RRScale) {

}

RRSwitch::RRSwitch() : MotionProfileExecutor("Right->Right Switch",8.0,mp::RRSwitch) {

}


CLSwitch::CLSwitch() : MotionProfileExecutor("center->left switch",8.0,mp::CLSwitch){
}

LFwd::LFwd() : MotionProfileExecutor("left fwd",10,mp::LFwd){

}

LLScale::LLScale() : MotionProfileExecutor("left->left scale",12,mp::LLScale) {
}

LLSwitch::LLSwitch() : MotionProfileExecutor("left->left switch", 8.0, mp::LLSwitch) {

}

RFwd::RFwd() : MotionProfileExecutor("right fwd",10,mp::RFwd){

}

RLScale::RLScale() :MotionProfileExecutor("right->left scale",12,mp::RLScale) {
}

LRScale::LRScale() : MotionProfileExecutor("left -> right scale",12,mp::LRScale) {

}
