//
// Created by Jason Markham on 2/20/18.
//

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
    WaitForMotionCompletion(MotionProfileExecutor* _executor,double _completionPercent = 1.0)
            : frc::Command(), exec(_executor), completionPercent(_completionPercent)
    {

    }

protected:
    bool IsFinished() override {
        return exec->IsCompleted() || exec->getPercentCompleted() >= completionPercent;
    }

    MotionProfileExecutor* exec;
    double completionPercent;
};

ScaleAuto::ScaleAuto(MotionProfileExecutor *exec) {

    AddSequential(exec);
    AddParallel([exec]() {
        auto g1 = new CommandGroup();
        g1->AddSequential(new WaitForMotionCompletion(exec, 0.7));
        g1->AddSequential(new GoToScale(),3.0);
        return g1;
    }());
    AddSequential(new DriveForward(6.0));
    AddSequential(new DumpCube());
    AddSequential(new DriveForward(-24.0));
    AddSequential(new StowBucket());


//    AddSequential(new ScaleDumpSequence());
//    AddSequential(new DriveForward(-6.0),0.7);
//    AddParallel(new ClampTiltToCube());

}

LLScaleAuto::LLScaleAuto() : ScaleAuto(new LLScale){}

RRScaleAuto::RRScaleAuto() : ScaleAuto(new RRScale()) {}

RLScaleAuto::RLScaleAuto() : ScaleAuto(new RLScale()) {}

LRScaleAuto::LRScaleAuto() : ScaleAuto(new LRScale()) {}
