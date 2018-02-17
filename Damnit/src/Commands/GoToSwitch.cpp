#include "GoToSwitch.h"
#include "BucketTiltPosition.h"
#include "UpperTiltPosition.h"
#include "StowClamp.h"
using namespace commands;

GoToSwitch::GoToSwitch() : frc::CommandGroup("Go To Switch") {
	// stow clamp
	AddSequential(new StowClamp);  // Hide clamp

	AddParallel(Buckets::getInstance().to_home_tweak(-16));//new BucketTiltPosition(-16));  // Put bucket in auto level
	AddParallel(new UpperTiltPosition(100));//(Buckets::getInstance().to_switch());//new UpperTiltPosition(150));  // move arm to switch
}
