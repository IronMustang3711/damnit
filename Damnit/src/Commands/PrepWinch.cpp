//
// Created by Jason Markham on 2/16/18.
//

#include <Robot.h>
#include <ReaderBoard.h>
#include "PrepWinch.h"
#include "UpperTiltPosition.h"
#include "BucketTiltPosition.h"
#include "Delay.h"
#include "BucketTiltPosition.h"
#include "StowClamp.h"
PrepWinch::PrepWinch() : frc::CommandGroup("prepare winch for latching") {
    Requires(Robot::winch.get());
    Requires(Robot::upperTilt.get());
    Requires(Robot::bucket.get());
    Requires(Robot::clamp.get());
    Requires(Robot::clampTilt.get());
   // The two above were added by Scott, please double check

    auto g2 = new frc::CommandGroup();
    g2->AddSequential(new Delay(0.5));
    g2->AddParallel(new BucketTiltToWinch());//(new BucketTiltPosition(217)); //212

   // The two below were added by Scott, please double check
   // AddSequential(new ClampOpen());
   // AddSequential(new ClampTiltToHome());
    AddSequential(new StowClamp, 1.5);
    AddSequential(new BucketTiltAllTheWayBack(),0.2);
    AddParallel(g2);
    AddParallel(new UpperTiltToWinch()); //508





}

void PrepWinch::Initialize() {
    CommandGroup::Initialize();
    ReaderBoard::reportWinch();
}
