#include "StowBucket.h"
#include "bucketTiltPosition.h"
#include "UpperTiltPosition.h"
#include "StowClamp.h"
StowBucket::StowBucket() : frc::CommandGroup("Stow Bucket"){
	AddSequential(new StowClamp);  // Hide clamp.  Should already be hid
	AddSequential(new BucketTiltPosition(-15));//(new BucketTiltPosition(-15));  // Back to home
	AddSequential(new UpperTiltToHome());  // move arm to home
	AddSequential(new BucketTiltToHome());//(new BucketTiltPosition(0));  // Back to home

}
