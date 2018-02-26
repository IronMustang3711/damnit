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
CRSwitch::CRSwitch() : MotionProfileExecutor("Center->Right Switch",12.0,mp::CRSwitch) {

}

CRScale::CRScale(): MotionProfileExecutor("Center->Right Scale",12.0,mp::CRScale)  {

}

Straight_10ft::Straight_10ft() : MotionProfileExecutor("straight 10ft",10.0,mp::DriveStraight_10ft) {

}

RRScale::RRScale() : MotionProfileExecutor("Right->Right Scale", 12.0,mp::RRScale) {

}

RRSwitch::RRSwitch() : MotionProfileExecutor("Right->Right Switch",10.0,mp::RRSwitch) {

}

CLScale::CLScale() : MotionProfileExecutor("center->left scale",12,mp::CLScale) {
}

CLSwitch::CLSwitch() : MotionProfileExecutor("center->left switch",10,mp::CLSwitch){
}

LFwd::LFwd() : MotionProfileExecutor("left fwd",10,mp::LFwd){

}

LLScale::LLScale() : MotionProfileExecutor("left->left scale",12,mp::LLScale) {
}

LLSwitch::LLSwitch() : MotionProfileExecutor("left->left switch", 10, mp::LLSwitch) {

}

RFwd::RFwd() : MotionProfileExecutor("right fwd",10,mp::RFwd){

}
