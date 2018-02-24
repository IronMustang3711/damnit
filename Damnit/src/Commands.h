//
// Created by Jason Markham on 2/23/18.
//

#ifndef DAMNIT_COMMANDS_H
#define DAMNIT_COMMANDS_H


#include "Commands/DriveArmsWithJoystick.h"
#include "Commands/ClampPosition.h"
#include "Commands/ToggleCommand.h"
#include "Commands/ClampTiltPosition.h"
#include "Commands/GoToScale.h"
#include "Commands/GoToSwitch.h"
#include "Commands/DumpCube.h"
#include "Commands/StowBucket.h"
#include "Commands/WinchCommands.h"
#include "Commands/PrepWinch.h"
#include "Commands/ToggleDirection.h"
#include <SmartDashboard/SmartDashboard.h>
#include "Commands/BucketTiltPosition.h"
#include "Commands/UpperTiltPosition.h"
#include "Commands/Delay.h"
#include "Commands/DriveWithJoystick.h"
#include "Commands/CurvatureDrive.h"

struct Commands {

    ClampOpen clampOpen;
    ClampClose clampClose;
    ToggleCommand clampToggle{"toggle clamp", &clampOpen, &clampClose};

    ClampTiltToSwitch clampTiltToSwitch;
    ClampTiltToBucket clampTiltToBucket;
    ClampTiltToCube clampTiltToCube;
    ClampTiltToHome clampTiltToHome;

    BucketTiltAutoLevel bucketTiltAutoLevel;
    BucketTiltToScale bucketTiltToScale;
    BucketTiltAllTheWayBack bucketTiltBack;
    BucketTiltAutoDump bucketTiltAutoDump;
    BucketTiltToWinch bucketTiltToWinch;
    BucketTiltToHome bucketTiltToHome;

    UpperTiltToScale upperTiltToScale;
    UpperTiltToSwitch upperTiltToSwitch;
    UpperTiltToHome upperTiltToHome;
    UpperTiltToWinch upperTiltToWinch;




    WinchUp winchUp;
    WinchDown winchDown;
    WinchHold winchHold;
    WinchDisable winchDisable;



    DriveWithJoystick driveWithJoystick;
    CurvatureDrive curvatureDrive;

    DriveArmsWithJoystick driveArmsWithJoystick;


    ToggleDirection toggleDirection;


    Delay halfSecondDelay{0.5};

//    CommandGroup stowClamp{"stow clamp"};
//
//    CommandGroup goToScale{"go to scale"};
//    CommandGroup goToSwitch{"go to switch"};
//    CommandGroup stowBucket{"stow bucket"};
//
//    CommandGroup delayedBucketTiltToWinch{"delayed bucket tilt to winch"};
//    CommandGroup winchPrep{"winch prep*"};
//
//    CommandGroup dumpCube{"dump cube"};
//
//    CommandGroup switchDumpSequence{"switch dump sequence *"};
//    CommandGroup scaleDumpSequence{"scale dump sequence*"};





    Commands();


};


#endif //DAMNIT_COMMANDS_H
