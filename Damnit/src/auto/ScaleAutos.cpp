//
// Created by Jason Markham on 2/20/18.
//

#include <Commands/Delay.h>
#include "Commands/UpperTiltPosition.h"
#include "Commands/BucketTiltPosition.h"
#include "Commands/DumpCube.h"
#include "Commands/StowBucket.h"
#include "Commands/GoToScale.h"
#include "Commands/ClampTiltPosition.h"
#include "ScaleAutos.h"
#include "ScaleDumpSequence.h"
#include "DriveForward.h"
#include "MotionProfileExecutors.h"

class WaitForMotionCompletion : public frc::Command {
public:
    explicit WaitForMotionCompletion(MotionProfileExecutor* _executor,Command* commandToStart,double _completionPercent = 1.0)
            : frc::Command(_completionPercent*_executor->getNominalDuration()), exec(_executor),cmd(commandToStart),  completionPercent(_completionPercent)
    {

    }

protected:
    bool IsFinished() override {
        return IsTimedOut() ||  exec->getPercentCompleted() >= completionPercent;
    }
    void End() override {
        DriverStation::ReportWarning("starting "+cmd->GetName());
        cmd->Start();
    }

    MotionProfileExecutor* exec;
    Command* cmd;
    double completionPercent;
};

ScaleAuto::ScaleAuto(MotionProfileExecutor *e) : exec(e) {

//

    AddSequential(exec);

   // AddParallel(new WaitForMotionCompletion(exec,new GoToScale(), 0.5));
//    AddParallel([exec]() {
//        auto g1 = new CommandGroup("switch g1");
//        g1->AddSequential(new Delay(3.0),3.0);
//       // g1->AddSequential(new WaitForMotionCompletion(exec,new GoToScale(), 0.7));
//        g1->AddSequential(new GoToScale());
//        return g1;
//    }());


   // AddSequential(new WaitForMotionCompletion(exec,new GoToScale(), 0.5));
   // AddParallel(exec);
   // AddSequential(new DriveForward(12.0));
   // AddSequential(new DumpCube());
   // AddSequential(new DriveForward(24.0));
  //  AddSequential(new StowBucket());


//    AddSequential(new ScaleDumpSequence());
//    AddSequential(new DriveForward(-6.0),0.7);
//    AddParallel(new ClampTiltToCube());

}

void ScaleAuto::Initialize() {
    CommandGroup::Initialize();

    auto thing = new WaitForMotionCompletion(exec,new GoToScale(), 0.5);
    thing->Start();
    thing->SetRunWhenDisabled(true); //TODO TEST!!!!!
    auto thing2 = new WaitForMotionCompletion(exec, new DumpCube(),1.0);
    //thing2->SetRunWhenDisabled(true);

    thing2->Start();

//    auto thing2 = new CommandGroup();
//    thing2->AddSequential(new WaitForMotionCompletion(exec, new DumpCube(),1.0));
//    thing2->AddSequential(new DriveForward(-32));
//    thing2->AddSequential(new StowBucket());
//
//    thing2->Start();
}

LLScaleAuto::LLScaleAuto() : ScaleAuto(new LLScale){}

RRScaleAuto::RRScaleAuto() : ScaleAuto(new RRScale()) {}

RLScaleAuto::RLScaleAuto() : ScaleAuto(new RLScale()) {}

LRScaleAuto::LRScaleAuto() : ScaleAuto(new LRScale()) {}
