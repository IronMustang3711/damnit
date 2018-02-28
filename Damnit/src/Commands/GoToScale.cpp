#include <ReaderBoard.h>
#include "GoToScale.h"
#include "BucketTiltPosition.h"
#include "UpperTiltPosition.h"
#include "StowClamp.h"

GoToScale::GoToScale() : frc::CommandGroup("Go To Scale") {

	/*  rod's original code:

	 GoToScale...

	 // stow clamp
	AddSequential(new StowClamp);  // Hide clamp

	AddParallel(new BucketTiltPosition(100));  // Put bucket in auto level
	AddParallel(new UpperTiltPosition(430));  // move arm to scale
	 ----------------------------------------
	 and GoToSwitch...

	 // stow clamp
	AddSequential(new StowClamp);  // Hide clamp

	AddParallel(new BucketTiltPosition(100));  // Put bucket in auto level
	AddParallel(new UpperTiltPosition(150));  // move arm to switch

	 */


	AddSequential(new StowClamp);
	//AddParallel(new BucketTiltAllTheWayBack(),0.5);

	AddParallel(new BucketTiltAutoLevel);

	AddParallel(new UpperTiltToScale());


	//TODO: try this if the above sequence isnt working
//	auto bucketTiltSequence = new CommandGroup();
//	bucketTiltSequence->AddSequential(new BucketTiltAllTheWayBack,0.5);
//	bucketTiltSequence->AddSequential(new BucketTiltAutoLevel);
//
//	AddSequential(new StowClamp);
//	AddSequential(bucketTiltSequence);
//	AddParallel(new UpperTiltToScale);
}

void GoToScale::Initialize() {
    CommandGroup::Initialize();
	ReaderBoard::reportGoToScale();
}
