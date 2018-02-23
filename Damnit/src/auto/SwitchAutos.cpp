//
// Created by Jason Markham on 2/20/18.
//

#include <Commands/BucketTiltPosition.h>
#include <Subsystems/ClampTilt.h>
#include <Commands/ClampTiltPosition.h>
#include "SwitchAutos.h"
#include "SwitchDumpSequence.h"
#include "DriveForward.h"

SwitchAuto::SwitchAuto(MotionProfileExecutor *exec) : frc::CommandGroup(exec->GetName()+" auto sequence") {
    AddSequential(exec);
    AddSequential(new SwitchDumpSequence());
    AddSequential(new DriveForward(-6.0),0.7);
    AddParallel(new ClampTiltToSwitch());
}