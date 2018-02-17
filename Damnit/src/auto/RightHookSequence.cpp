//
// Created by Jason Markham on 2/17/18.
//

#include <Commands/GoToSwitch.h>
#include <Commands/DumpCube.h>
#include <Commands/StowBucket.h>
#include "RightHookSequence.h"
#include "MotionProfileCommand.h"
#include "DriveForward.h"
#include "MotionProfileCommand2.h"


RightHookSequence::RightHookSequence(bool toSwitch) : frc::CommandGroup("right") {
    if(toSwitch)
        AddSequential(new MotionProfileCommand());
    else
        AddSequential(new MotionProfileCommand2());

    AddSequential(new GoToSwitch());
    AddSequential(new DumpCube());
    AddSequential(new DriveForward(-12.0),1.0);
    AddParallel(new StowBucket(),2.0);
}
