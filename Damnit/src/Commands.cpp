//
// Created by Jason Markham on 2/23/18.
//

#include "Commands.h"

Commands::Commands() {
//    stowClamp.AddSequential(&clampOpen);
//    stowClamp.AddSequential(&clampTiltToHome);
//
//    goToScale.AddSequential(&stowClamp);
//    goToScale.AddParallel(&bucketTiltAutoLevel);
//    goToScale.AddParallel(&upperTiltToScale);
//
//    goToSwitch.AddSequential(&stowClamp);
//    goToSwitch.AddParallel(&bucketTiltBack);
//    goToSwitch.AddParallel(&upperTiltToSwitch);
//
//    stowBucket.AddSequential(&stowClamp);
//    stowBucket.AddSequential(&bucketTiltBack);
//    stowBucket.AddSequential(&upperTiltToHome);
//    stowBucket.AddSequential(&bucketTiltToHome);
//
//    delayedBucketTiltToWinch.AddSequential(&halfSecondDelay);
//    delayedBucketTiltToWinch.AddParallel(&bucketTiltToWinch);
//
//    winchPrep.AddSequential(&bucketTiltBack, 0.4);
//    winchPrep.AddParallel(&delayedBucketTiltToWinch);
//    winchPrep.AddParallel(&upperTiltToWinch);
//
//    dumpCube.AddSequential(&bucketTiltAutoDump,1.0);
//    dumpCube.AddSequential(&halfSecondDelay);
//    dumpCube.AddSequential(&bucketTiltBack);
//
//    switchDumpSequence.AddSequential(&goToSwitch);
//    switchDumpSequence.AddSequential(&dumpCube);
//    switchDumpSequence.AddSequential(&stowBucket);
//
//    scaleDumpSequence.AddSequential(&goToScale);
//    scaleDumpSequence.AddSequential(&dumpCube);
//    scaleDumpSequence.AddSequential(&stowBucket);


//    for (auto c : std::initializer_list<Sendable*> {
//            &clampOpen,
//            &clampClose,
//            &clampToggle,
//            &clampTiltToSwitch,
//            &clampTiltToBucket,
//            &clampTiltToCube,
//            &clampTiltToHome,
//            &bucketTiltAutoLevel,
//            //&bucketTiltToScale,
//            &bucketTiltBack,
//            &bucketTiltAutoDump,
//            &bucketTiltToWinch,
//            &bucketTiltToHome,
//            &upperTiltToScale,
//            &upperTiltToSwitch,
//            &upperTiltToHome,
//            &upperTiltToWinch,
////            &winchUp,
////            &winchDown,
////            &winchHold,
////            &winchDisable,
//            &driveArmsWithJoystick,
//            &toggleDirection,
//            &halfSecondDelay,
////            &stowClamp,
////            &goToScale,
////            &goToSwitch,
////            &stowBucket,
////            &delayedBucketTiltToWinch,
////            &winchPrep,
////            &dumpCube,
////            &switchDumpSequence,
////            &scaleDumpSequence
//
//    }) {
//        SmartDashboard::PutData(c);
//    }


}