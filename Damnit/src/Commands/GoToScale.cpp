#include "GoToScale.h"
#include "BucketTiltPosition.h"
#include "UpperTiltPosition.h"
#include "StowClamp.h"

GoToScale::GoToScale() : frc::CommandGroup("Go To Scale") {
	// stow clamp
	AddSequential(new StowClamp);  // Hide clamp

	AddParallel(new BucketTiltAutoLevel());//(new BucketTiltPosition(100));  // Put bucket in auto level
	AddParallel(new UpperTiltToScale());  // move arm to scale
}
