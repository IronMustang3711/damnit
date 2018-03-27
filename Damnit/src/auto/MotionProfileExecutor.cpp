//
// Created by Jason Markham on 2/19/18.
//

#include "Robot.h"
#include "MotionProfileExecutor.h"
#include <thread>
#include <chrono>
using namespace std::chrono_literals;

MotionProfileExecutor::MotionProfileExecutor(const llvm::Twine &name, double timeout,const std::vector<mp::Prof>& _profs)
        : frc::Command(name,timeout), profiles(_profs)
{
    Requires(Robot::chassis.get());

    left = RobotMap::chassisLeftFront.get();
    right = RobotMap::chassisRightFront.get();

    double expected_time = profiles.size() / 100.0;
    SetTimeout(expected_time + 0.5);



    notifier = std::make_unique<Notifier>(&MotionProfileExecutor::update, this);


}

void MotionProfileExecutor::Initialize() {
    Robot::chassis->prepareForAutonomous();
    IMotorController& lRef = *left;
    IMotorController& rRef = *right;

    RobotMap::chassisLeftRear->Follow(lRef);
    RobotMap::chassisRightRear1->Follow(rRef);

    fillIndex = 0;
    finished = false;


    for (auto t : {left, right}) {
        t->NeutralOutput();

        t->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder,PRIMARY_PID_IDX,TIMEOUT);

        t->NeutralOutput();

        t->SelectProfileSlot(CLOSED_LOOP_SLOT, PRIMARY_PID_IDX);
        constexpr double FGain = /*1.0*/(0.9/*percent*/ * 1023.0/*10 bit SRX max*/) / 1100.0; /*max v*/

        t->Config_kF(CLOSED_LOOP_SLOT, FGain, TIMEOUT);
        t->Config_kP(CLOSED_LOOP_SLOT, 0.5, TIMEOUT); // 25
        t->Config_kI(CLOSED_LOOP_SLOT, 0.0, TIMEOUT);
        t->Config_kD(CLOSED_LOOP_SLOT, 0.0, TIMEOUT); //10

       // t->ConfigAllowableClosedloopError(PRIMARY_PID_IDX,10,TIMEOUT);

        t->ConfigMotionProfileTrajectoryPeriod(0, TIMEOUT); //duration already set in profile array

        //TODO this can be removed once it's working correctly?
        t->SetStatusFramePeriod(StatusFrameEnhanced::Status_10_Targets, 10, TIMEOUT);

        t->SetControlFramePeriod(Control_3_General, 10); //TODO: Control_6_MotProfAddTrajPoint?


        t->ChangeMotionControlFramePeriod(5);

        t->ClearMotionProfileTrajectories();

        t->Set(ControlMode::MotionProfile, SetValueMotionProfile::Disable);



       // t->GetSensorCollection().SetQuadraturePosition(0, TIMEOUT);
        //t->SetSelectedSensorPosition(0, CLOSED_LOOP_SLOT, TIMEOUT);

       frc::Wait(0.2);


    }
    DriverStation::ReportWarning("init: "+GetName());
    SmartDashboard::PutNumber("profile duration",getNominalDuration());

    fill();

    notifier->StartPeriodic(0.005);

}

void MotionProfileExecutor::Execute() {
    update();
    fill();
    for (auto t : {left, right}) {

        MotionProfileStatus status{};

        t->GetMotionProfileStatus(status);

       // SmartDashboard::PutNumber("top buffer Rem",status.topBufferRem);
        SmartDashboard::PutNumber("top buffer Cnt",status.topBufferCnt);
        SmartDashboard::PutNumber("bottom buffer Cnt",status.btmBufferCnt);
        SmartDashboard::PutNumber("profile progress %",getPercentCompleted());

        t->Set(ControlMode::MotionProfile, SetValueMotionProfile::Enable);


        if (status.btmBufferCnt > 5) {
            t->Set(ControlMode::MotionProfile, SetValueMotionProfile::Enable);
        } else if (status.activePointValid && status.isLast) {
            t->Set(ControlMode::MotionProfile, SetValueMotionProfile::Hold);
            DriverStation::ReportWarning("profile finished: "+GetName());
//            Cancel();
            finished = true;
        }


        //TODO more diagnostic messages from status


//        SmartDashboard::PutNumber("profile error: " + t->GetName(),
//                                  t->GetClosedLoopError(CLOSED_LOOP_SLOT));
//        SmartDashboard::PutNumber("target: " + t->GetName(),
//                                  t->GetClosedLoopTarget(CLOSED_LOOP_SLOT));
//        SmartDashboard::PutNumber("position: " + t->GetName(),
//                                  t->GetSelectedSensorPosition(CLOSED_LOOP_SLOT));
//        SmartDashboard::PutNumber("velocity: " + t->GetName(),
//                                  t->GetSelectedSensorVelocity(CLOSED_LOOP_SLOT));
//
//        SmartDashboard::PutNumber("trajectory position: " + t->GetName(),
//                                  t->GetActiveTrajectoryPosition());
//        SmartDashboard::PutNumber("trajectory velocity: " + t->GetName(),
//                                  t->GetActiveTrajectoryVelocity());

    }
}

bool MotionProfileExecutor::IsFinished() {
    return finished || IsTimedOut();
}

void MotionProfileExecutor::End() {
    fillIndex = 0;
    if(IsTimedOut()){
        DriverStation::ReportWarning("timed out: "+GetName());
    }
    notifier->Stop();
    DriverStation::ReportWarning("end: "+GetName());
}

void MotionProfileExecutor::update() {
    for (auto t : {left, right}) t->ProcessMotionProfileBuffer();
}

void MotionProfileExecutor::fill() {
    TrajectoryPoint leftPoint{};
    TrajectoryPoint rightPoint{};


    while (!left->IsMotionProfileTopLevelBufferFull()
           && !right->IsMotionProfileTopLevelBufferFull()
           && fillIndex < profiles.size()) {


        leftPoint.zeroPos = rightPoint.zeroPos = (fillIndex == 0);
        leftPoint.isLastPoint = rightPoint.isLastPoint = (fillIndex == profiles.size()-1);
        leftPoint.timeDur = rightPoint.timeDur = TrajectoryDuration_10ms;

        leftPoint.position = profiles[fillIndex].leftPosition;
        leftPoint.velocity = profiles[fillIndex].leftVelocity;


        rightPoint.position =  profiles[fillIndex].rightPosition;
        rightPoint.velocity =  profiles[fillIndex].rightVelocity;

        left->PushMotionProfileTrajectory(leftPoint);
        right->PushMotionProfileTrajectory(rightPoint);

        fillIndex++;
    }

}

void MotionProfileExecutor::Interrupted() {
    DriverStation::ReportWarning("interrupted: "+this->GetName());
    Command::Interrupted();
}

double MotionProfileExecutor::getPercentCompleted() {
    double topBufRemaining = ( left->GetMotionProfileTopLevelBufferCount() + right->GetMotionProfileTopLevelBufferCount()) / 2.0;
    double localRemaining = (profiles.size() - fillIndex);
    double totalRemaining = topBufRemaining + localRemaining;

    return 1.0 - (totalRemaining/profiles.size());
}

//seconds
double MotionProfileExecutor::getNominalDuration() {
    return profiles.size() / 100.0;
}


