#include "StowBucket.h"
#include "bucketTiltPosition.h"
#include "UpperTiltPosition.h"
#include "StowClamp.h"

StowBucket::StowBucket() {
	AddSequential(new StowClamp);  // Hide clamp.  Should already be hid
	AddSequential(new BucketTiltPosition(-6));  // Back to home %rod15
	AddSequential(new UpperTiltPosition(0));  // move arm to home
	AddSequential(new BucketTiltPosition(0));  // Back to zero
}
