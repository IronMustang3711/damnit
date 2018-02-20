//
// Created by Jason Markham on 2/19/18.
//

#include <Commands/GoToSwitch.h>
#include <Commands/DumpCube.h>
#include <Commands/StowBucket.h>
#include <Robot.h>
#include "SwitchDumpSequence.h"

SwitchDumpSequence::SwitchDumpSequence() : frc::CommandGroup("switch dump") {
    AddSequential(new GoToSwitch());
    AddSequential(new DumpCube());

    AddSequential(new StowBucket());

   // AddSequential(new DriveForward(-12.0),1.0);
   // AddParallel(new StowBucket(),2.0);


}

void SwitchDumpSequence::End() {
    Robot::bucket->Disable();
    Robot::upperTilt->Disable();
    Robot::clampTilt->Disable();
    Robot::clamp->Disable();
}
