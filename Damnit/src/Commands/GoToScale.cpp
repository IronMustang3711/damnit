#include "GoToScale.h"
#include "Commands/BucketTiltPosition.h"
#include "Commands/UpperTiltPosition.h"
#include "Commands/StowClamp.h"

GoToScale::GoToScale() {
	// stow clamp
	AddSequential(new StowClamp);  // Hide clamp

	AddParallel(new BucketTiltPosition(100));  // Put bucket in auto level
	AddParallel(new UpperTiltPosition(430));  // move arm to scale
}
