/*
 * MotionProfileCommand.cpp
 *
 *  Created on: Feb 14, 2018
 *      Author: jason
 */

#include <motion/MotionProfileCommand.h>
#include <Robot.h>
#include "profile.h"

using namespace mp;

//TODO: remove timeout once this is working.
MotionProfileCommand::MotionProfileCommand() : frc::Command("Motion Profile", 5.0) {
    auto c = Robot::chassis.get();
    Requires(c);

    left = RobotMap::chassisLeftFront.get();
    right = RobotMap::chassisRightFront.get();

    notifier = std::make_unique<Notifier>(&MotionProfileCommand::update, this);

}

void MotionProfileCommand::Initialize() {

    it = PROFS.cbegin();


    for (auto t : {left, right}) {
        t->SelectProfileSlot(SLOT, TIMEOUT);

        constexpr double FGain = (0.8/*percent*/ * 1023.0/*10 bit SRX max*/) / 1100.0; /*max v*/

        t->Config_kF(SLOT, FGain, TIMEOUT);
        t->Config_kP(SLOT, 0.0, TIMEOUT);
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

    fill(std::next(PROFS.cbegin(), 20));

    notifier->StartPeriodic(0.05);
}

void MotionProfileCommand::Execute() {
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
            DriverStation::ReportError("something weird happening in MotionProfileCommand::Execute");
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

bool MotionProfileCommand::IsFinished() {
    return false; //we will cancel ourselves
}

void MotionProfileCommand::End() {
    notifier->Stop();
}

void MotionProfileCommand::update() {
    for (auto t : {left, right}) t->ProcessMotionProfileBuffer();

}

void MotionProfileCommand::fill(ProfIter stop) {
    TrajectoryPoint leftPoint{};
    TrajectoryPoint rightPoint{};

    while (!left->IsMotionProfileTopLevelBufferFull()
           && !right->IsMotionProfileTopLevelBufferFull()
           && it != stop) {

        leftPoint.zeroPos = rightPoint.zeroPos = (it == &PROFS.front());
        leftPoint.isLastPoint = rightPoint.isLastPoint = (it == &PROFS.back());
        leftPoint.timeDur = rightPoint.timeDur = TrajectoryDuration_10ms;

        leftPoint.position = it->leftPosition;
        leftPoint.velocity = it->leftVelocity / 600.0; //100 ms interval //TODO: do this during codegen
        //TODO: also, is that correct?

        rightPoint.position = it->rightPosition;
        rightPoint.velocity = it->rightVelocity / 600.0;

        left->PushMotionProfileTrajectory(leftPoint);
        right->PushMotionProfileTrajectory(rightPoint);

        it++;
    }
}

