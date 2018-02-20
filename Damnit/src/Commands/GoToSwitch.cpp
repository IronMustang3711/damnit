#include "GoToSwitch.h"
#include "BucketTiltPosition.h"
#include "UpperTiltPosition.h"
#include "StowClamp.h"

GoToSwitch::GoToSwitch() : frc::CommandGroup("Go To Switch") {
	// stow clamp
	AddSequential(new StowClamp);  // Hide clamp

	AddParallel(new BucketTiltPosition(-16));//new BucketTiltPosition(-16));  // Put bucket in auto level
	AddParallel(new UpperTiltToSwitch());//new UpperTiltPosition(150));  // move arm to switch
}
