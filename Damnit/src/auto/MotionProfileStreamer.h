//
// Created by Jason Markham on 3/27/18.
//
#pragma once


#include "profile.h"
#include "Robot.h"
#include <iterator>
#include <llvm/ArrayRef.h>
#include <iterator>


template
        <typename Iter>
class MotionProfileStreamer: public frc::Command {

    static constexpr int CLOSED_LOOP_SLOT = 0;
    static constexpr int PRIMARY_PID_IDX = 0;
    static constexpr int TIMEOUT = 10;
    void update(){

    }

    void fill(){
        TrajectoryPoint leftPoint{};
        TrajectoryPoint rightPoint{};

        for(; !(left->IsMotionProfileTopLevelBufferFull()|| right->IsMotionProfileTopLevelBufferFull())
              && current != end;
                ++current){




            leftPoint.zeroPos = rightPoint.zeroPos
                    = (current == begin);
            leftPoint.isLastPoint = rightPoint.isLastPoint
                    = (current == end);
            leftPoint.timeDur = rightPoint.timeDur
                    = TrajectoryDuration_10ms;

            leftPoint.position = current->leftPosition;
            leftPoint.velocity = current->leftVelocity;


            rightPoint.position =  current->rightPosition;
            rightPoint.velocity =  current->rightVelocity;

            left->PushMotionProfileTrajectory(leftPoint);
            right->PushMotionProfileTrajectory(rightPoint);
        }

    }


    std::unique_ptr<frc::Notifier> notifier;
    WPI_TalonSRX *left;
    WPI_TalonSRX *right;


    const Iter begin;
    const Iter end;
    Iter current;

    bool finished = false;

public:
    MotionProfileStreamer(Iter _begin, Iter _end)
            : begin(_begin), end(_end), current(_begin)
    {

        left = RobotMap::chassisLeftFront.get();
        right = RobotMap::chassisRightFront.get();

        notifier = std::make_unique<Notifier>(&MotionProfileStreamer::update, this);

        double max_time = std::distance(begin,end) / 100.0 + 0.5;
        SetTimeout(max_time);

    }

    void Initialize() override {
        Robot::chassis->prepareForAutonomous();
        IMotorController& lRef = *left;
        IMotorController& rRef = *right;

        RobotMap::chassisLeftRear->Follow(lRef);
        RobotMap::chassisRightRear1->Follow(rRef);

        current = begin;
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

    double getNominalDuration(){
        return std::distance(begin,end) / 100.0;
    }

    double getProgress(){
        double topBufRemaining = ( left->GetMotionProfileTopLevelBufferCount() + right->GetMotionProfileTopLevelBufferCount()) / 2.0;
        double localRemaining = std::distance(current,end);
        double totalRemaining = topBufRemaining + localRemaining;

        return 1.0 - (totalRemaining/double(std::distance(begin,end)));

    }

    bool IsFinished() override {
        return IsTimedOut();
    }





};

namespace mp {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
    constexpr inline bool constexprTestPart(){
        constexpr std::array<mp::Prof, 1> profs{mp::Prof()};
        static_assert(mp::profCompileTest(),"profCompileTest");

//
//        Command *c = new MotionProfileStreamer<decltype(profs.begin())>(profs.begin(), profs.end());
//        Command *c2 = new MotionProfileStreamer<decltype(profs.rbegin())>(profs.rbegin(), profs.rend());

        return true;
    }
    inline void compileTest() {
        mp::constexprTestPart();

        std::array<mp::Prof, 1> profs{mp::Prof()};
         std::vector<mp::Prof> profVector{};
        auto bi = std::back_inserter(profVector);

        Command *c = new MotionProfileStreamer<decltype(profs.begin())>(profs.begin(), profs.end());
        Command *c2 = new MotionProfileStreamer<decltype(profs.rbegin())>(profs.rbegin(), profs.rend());
        Command *c3 = new MotionProfileStreamer<decltype(profVector.begin())>(profVector.begin(),profVector.end());

    }
#pragma GCC diagnostic pop
}


