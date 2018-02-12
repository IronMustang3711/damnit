#include "StowBucket.h"
#include "bucketTiltPosition.h"
#include "UpperTiltPosition.h"
#include "StowClamp.h"

StowBucket::StowBucket() {
	AddSequential(new StowClamp);  // Hide clamp.  Should already be hid
	AddSequential(new BucketTiltPosition(-15));  // Back to home
	AddSequential(new UpperTiltPosition(0));  // move arm to home
}
