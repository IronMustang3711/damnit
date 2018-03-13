//
// Created by Jason Markham on 2/20/18.
//

#include "Commands/ClampTiltPosition.h"
#include "ScaleAutos.h"
#include "ScaleDumpSequence.h"
#include "DriveForward.h"
#include "MotionProfileExecutors.h"

ScaleAuto::ScaleAuto(MotionProfileExecutor *exec) {
    AddSequential(exec);
    AddSequential(new ScaleDumpSequence());
    AddSequential(new DriveForward(-6.0),0.7);
    AddParallel(new ClampTiltToCube());

}

LLScaleAuto::LLScaleAuto() : ScaleAuto(new LLScale){}

RRScaleAuto::RRScaleAuto() : ScaleAuto(new RRScale()) {}

RLScaleAuto::RLScaleAuto() : ScaleAuto(new RLScale()) {}

LRScaleAuto::LRScaleAuto() : ScaleAuto(new LRScale()) {}
