//
// Created by Jason Markham on 2/17/18.
//

#include "MotionProfileCommand2.h"

/*
 * MotionProfileCommand2.cpp
 *
 *  Created on: Feb 14, 2018
 *      Author: jason
 */

#include <Robot.h>
#include "profile.h"

using namespace mp;
using namespace frc;
//TODO: remove timeout once this is working.
MotionProfileCommand2::MotionProfileCommand2() : frc::Command("Motion Profile 2", 12.0) {
    auto c = Robot::chassis.get();
    Requires(c);

    left = RobotMap::chassisLeftFront.get();
    right = RobotMap::chassisRightFront.get();

    notifier = std::make_unique<Notifier>(&MotionProfileCommand2::update, this);

}

void MotionProfileCommand2::Initialize() {

    it = RIGHT_HOOK_TO_SCALE.cbegin();


    for (auto t : {left, right}) {
        t->SelectProfileSlot(SLOT, TIMEOUT);


        /*
         *
        t->Config_kP(SLOT, 10.0, TIMEOUT);
        t->Config_kI(SLOT, 0.0, TIMEOUT);
        t->Config_kD(SLOT, 0.0, TIMEOUT);
        t->Config_kF(SLOT, FGain, TIMEOUT);
         */

        constexpr double FGain = (1.0/*percent*/ * 1023.0/*10 bit SRX max*/) / 1300.0; /*max v*/

        t->Config_kF(SLOT, FGain, TIMEOUT);
        t->Config_kP(SLOT, 5.0, TIMEOUT);
        t->Config_kI(SLOT, 0.0, TIMEOUT);
        t->Config_kD(SLOT, 0.0, TIMEOUT);

//        t->Config_kF(SLOT, 0.8, TIMEOUT);
//        t->Config_kP(SLOT, 20.0, TIMEOUT);
//        t->Config_kI(SLOT, 0.1, TIMEOUT);
//        t->Config_kD(SLOT, 30.0, TIMEOUT);

        t->ConfigMotionProfileTrajectoryPeriod(0, TIMEOUT); //duration already set in profile array

        //TODO this can be removed once it's working correctly?
        t->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, TIMEOUT);

        t->SetControlFramePeriod(Control_3_General, 10); //TODO: Control_6_MotProfAddTrajPoint?

        t->GetSensorCollection().SetQuadraturePosition(0, TIMEOUT);
        t->SetSelectedSensorPosition(0, SLOT, TIMEOUT);
        //TODO: what is the difference between these 2?

        t->Set(ControlMode::MotionProfile, SetValueMotionProfile::Disable);

        t->ClearMotionProfileTrajectories();

    }

    fill();

    notifier->StartPeriodic(0.005);
}

void MotionProfileCommand2::Execute() {
    update();
    fill();
    for (auto t : {left, right}) {

        MotionProfileStatus status{};

        t->GetMotionProfileStatus(status);

        if (status.btmBufferCnt > 5) {
            t->Set(ControlMode::MotionProfile, SetValueMotionProfile::Enable);
        } else if (status.activePointValid && status.isLast) {
            t->Set(ControlMode::MotionProfile, SetValueMotionProfile::Hold);
            Cancel();
        } else {
            DriverStation::ReportError("something weird happening in MotionProfileCommand2::Execute");
        }

        //TODO more diagnostic messages from status


        SmartDashboard::PutNumber("error: " + t->GetName(),
                                  t->GetClosedLoopError(SLOT));
        SmartDashboard::PutNumber("target: " + t->GetName(),
                                  t->GetClosedLoopTarget(SLOT));
        SmartDashboard::PutNumber("position: " + t->GetName(),
                                  t->GetSelectedSensorPosition(SLOT));
        SmartDashboard::PutNumber("velocity: " + t->GetName(),
                                  t->GetSelectedSensorVelocity(SLOT));

        SmartDashboard::PutNumber("trajectory position: " + t->GetName(),
                                  t->GetActiveTrajectoryPosition());
        SmartDashboard::PutNumber("trajectory velocity: " + t->GetName(),
                                  t->GetActiveTrajectoryVelocity());

    }


}

bool MotionProfileCommand2::IsFinished() {
    return IsTimedOut();
}

void MotionProfileCommand2::End() {
    notifier->Stop();
}

void MotionProfileCommand2::update() {
    for (auto t : {left, right}) t->ProcessMotionProfileBuffer();

}

void MotionProfileCommand2::fill(ProfIter stop) {
    TrajectoryPoint leftPoint{};
    TrajectoryPoint rightPoint{};

    while (!left->IsMotionProfileTopLevelBufferFull()
           && !right->IsMotionProfileTopLevelBufferFull()
           && it != stop) {

        leftPoint.zeroPos = rightPoint.zeroPos = (it == &RIGHT_HOOK_TO_SCALE.front());
        leftPoint.isLastPoint = rightPoint.isLastPoint = (it == &RIGHT_HOOK_TO_SCALE.back());
        leftPoint.timeDur = rightPoint.timeDur = TrajectoryDuration_10ms;

        leftPoint.position = it->leftPosition;
        leftPoint.velocity = it->leftVelocity;


        rightPoint.position = it->rightPosition;
        rightPoint.velocity = it->rightVelocity;

        left->PushMotionProfileTrajectory(leftPoint);
        right->PushMotionProfileTrajectory(rightPoint);

        it++;
    }
}

