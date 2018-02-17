#include "StowBucket.h"
#include "bucketTiltPosition.h"
#include "UpperTiltPosition.h"
#include "StowClamp.h"
using namespace commands;
StowBucket::StowBucket() : frc::CommandGroup("Stow Bucket"){
	AddSequential(new StowClamp);  // Hide clamp.  Should already be hid
	AddSequential(Buckets::getInstance().to_home_tweak(-15));//(new BucketTiltPosition(-15));  // Back to home
	AddSequential(new UpperTiltPosition(0));  // move arm to home
	AddSequential(Buckets::getInstance().to_home());//(new BucketTiltPosition(0));  // Back to home

}
