//
// Created by Jason Markham on 2/20/18.
//

#include <Commands/ClampTiltPosition.h>
#include "ScaleAutos.h"
#include "ScaleDumpSequence.h"
#include "DriveForward.h"

ScaleAuto::ScaleAuto(MotionProfileExecutor *exec) {
    AddSequential(exec);
    AddSequential(new ScaleDumpSequence());
    AddSequential(new DriveForward(-6.0),0.7);
    AddParallel(new ClampTiltToCube());

}
