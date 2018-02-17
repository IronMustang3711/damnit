//
// Created by Jason Markham on 2/17/18.
//

#include <Commands/GoToSwitch.h>
#include <Commands/DumpCube.h>
#include <Commands/StowBucket.h>
#include "RightHookSequence.h"
#include "MotionProfileCommand.h"
#include "DriveForward.h"

RightHookSequence::RightHookSequence(): frc::CommandGroup("right hook") {
    AddSequential(new MotionProfileCommand());
    AddSequential(new GoToSwitch());
    AddSequential(new DumpCube());
    AddSequential(new DriveForward(-12.0),1.0);
    AddParallel(new StowBucket(),2.0);

}
