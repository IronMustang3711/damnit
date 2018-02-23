//
// Created by Jason Markham on 2/19/18.
//

#include <Robot.h>
#include <Commands/Delay.h>
#include <Commands/UpperTiltPosition.h>
#include <Commands/BucketTiltPosition.h>
#include <Commands/GoToSwitch.h>
#include <Commands/DumpCube.h>
#include <Commands/StowBucket.h>
#include <Commands/GoToScale.h>
#include <Commands/StowClamp.h>
#include "ScaleDumpSequence.h"

ScaleDumpSequence::ScaleDumpSequence() : frc::CommandGroup("scale dump") {

//    Requires(Robot::upperTilt.get());
//    Requires(Robot::bucket.get());

    auto g2 = new frc::CommandGroup();
    g2->AddSequential(new Delay(2.0));
    g2->AddSequential(new DumpCube());
    g2->AddSequential(new StowBucket());

    /*
     GoToScale:

	AddSequential(new StowClamp);  // Hide clamp

	AddParallel(new BucketTiltAutoLevel());//(new BucketTiltPosition(100));  // Put bucket in auto level
	AddParallel(new UpperTiltToScale());
     */

    auto myGroup = new CommandGroup("stow,to scale,dump");
    myGroup->AddSequential(new StowClamp);
    myGroup->AddSequential(new UpperTiltToScale());
    //myGroup->AddSequential(new DumpCube());
    //dump cube
    AddSequential(new BucketTiltAutoLevel());
    AddSequential(new Delay(0.5));
    AddSequential(new BucketTiltAllTheWayBack());//
    //dump cube

    AddSequential(myGroup);
    AddParallel(new BucketTiltAutoLevel);
    AddSequential(new StowBucket);







   // AddSequential(new DumpCube());

//    AddSequential(new Delay(0.5));
//    AddSequential(new StowBucket());
//    auto g2 = new frc::CommandGroup();
//    g2->AddSequential(new Delay(0.5));
////    g2->AddParallel(new BucketTiltPosition(0));//(new BucketTiltPosition(217)); //212
////
////    AddSequential(new BucketTiltPosition(),0.2);
//    AddParallel(g2);
//    AddParallel(new UpperTiltPosition(500)); //508


}

void ScaleDumpSequence::End() {
    Robot::bucket->Disable();
    Robot::upperTilt->Disable();
    Robot::clampTilt->Disable();
    Robot::clamp->Disable();
}
