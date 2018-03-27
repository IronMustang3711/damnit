//
// Created by Jason Markham on 2/20/18.
//

#include <Commands/ConditionalCommand.h>
#include <Robot.h>
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

//attempt at dealing with command group requirement constraints
//ConditionalCommand inherits and then removes constraints from child commands
//TODO: figure out how/if this will fix commandgroup issues
class Damnit : public frc::ConditionalCommand {
public:
    explicit Damnit(Command* c) : ConditionalCommand("damnit("+c->GetName()+")", c, nullptr) {}
    bool Condition() override {return true;}

};

class Hold : public frc::Command {
public:
//    double upper = 0;
//    double bucket = 0;
    Hold() : frc::Command("hold"){
        Requires(Robot::upperTilt.get());
        Requires(Robot::bucket.get());
        SetRunWhenDisabled(true);
    }
    void Initialize() override{
        Robot::upperTilt->Enable();
        Robot::bucket->Enable();
//        upper = Robot::upperTilt.get()->GetSetpoint();// GetPosition();
//        bucket = Robot::bucket.get()->GetSetpoint();//GetPosition();
    }
    void Execute() override  {
    Robot::upperTilt->Enable();
    Robot::bucket->Enable();
        Robot::upperTilt->SetSetpoint(400);
        Robot::bucket->SetSetpoint(205);

    }
    bool IsFinished() override {
        return false;
    }

};

ScaleAuto::ScaleAuto(MotionProfileExecutor *e) : exec(e)
{

    goToScale = new GoToScale();
    goToScale->SetRunWhenDisabled(true);
    thing = new WaitForMotionCompletion(exec,goToScale, 0.3);
    thing->SetRunWhenDisabled(true);

    dumpAndBack = new CommandGroup();
    dumpAndBack->AddSequential(new DumpCube());
    //dumpAndBack->AddSequential(new Hold());
    dumpAndBack->AddSequential( new DumbDriveForward(0.5));// DriveForward(-42.0,3.0));
    dumpAndBack->AddSequential(new StowBucket());

    //     thing2 = new WaitForMotionCompletion(exec, new DumpCube(),1.0);
    thing2 = new WaitForMotionCompletion(exec, dumpAndBack,1.0);



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
    thing->Start();
    thing2->Start();
}

LLScaleAuto::LLScaleAuto() : ScaleAuto(new LLScale){}

RRScaleAuto::RRScaleAuto() : ScaleAuto(new RRScale()) {}

RLScaleAuto::RLScaleAuto() : ScaleAuto(new RLScale()) {}

LRScaleAuto::LRScaleAuto() : ScaleAuto(new LRScale()) {}
