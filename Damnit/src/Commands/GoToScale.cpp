#include "GoToScale.h"
#include "BucketTiltPosition.h"
#include "UpperTiltPosition.h"
#include "StowClamp.h"

GoToScale::GoToScale() : frc::CommandGroup("Go To Scale") {
	// stow clamp
	AddSequential(new StowClamp);  // Hide clamp

	//TODO: this is probably wrong.
	AddParallel(new BucketTiltAllTheWayBack());//(new BucketTiltPosition(100));  // Put bucket in auto level
	AddParallel(new UpperTiltToScale());  // move arm to scale


	//TODO: try this if the above sequence isnt working
//	auto bucketTiltSequence = new CommandGroup();
//	bucketTiltSequence->AddSequential(new BucketTiltAllTheWayBack,0.5);
//	bucketTiltSequence->AddSequential(new BucketTiltAutoLevel);
//
//	AddSequential(new StowClamp);
//	AddSequential(bucketTiltSequence);
//	AddParallel(new UpperTiltToScale);
}
