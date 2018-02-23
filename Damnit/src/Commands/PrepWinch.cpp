//
// Created by Jason Markham on 2/16/18.
//

#include <Robot.h>
#include "PrepWinch.h"
#include "UpperTiltPosition.h"
#include "BucketTiltPosition.h"
#include "Delay.h"
#include "BucketTiltPosition.h"
PrepWinch::PrepWinch() : frc::CommandGroup("prepare winch for latching") {
    Requires(Robot::winch.get());
    Requires(Robot::upperTilt.get());
    Requires(Robot::bucket.get());

    auto g2 = new frc::CommandGroup();
    g2->AddSequential(new Delay(0.5));
    g2->AddParallel(new BucketTiltToWinch());//(new BucketTiltPosition(217)); //212

    AddSequential(new BucketTiltAllTheWayBack(),0.2);
    AddParallel(g2);
    AddParallel(new UpperTiltToWinch()); //508





}
