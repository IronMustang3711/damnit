#include "GoToSwitch.h"
#include "Commands/BucketTiltPosition.h"
#include "Commands/UpperTiltPosition.h"
#include "Commands/StowClamp.h"

GoToSwitch::GoToSwitch() {
	// stow clamp
	AddSequential(new StowClamp);  // Hide clamp

	AddParallel(new BucketTiltPosition(100));  // Put bucket in auto level
	AddParallel(new UpperTiltPosition(150));  // move arm to switch
}
