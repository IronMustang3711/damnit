#include "DumpCube.h"
#include "bucketTiltPosition.h"
#include "UpperTiltPosition.h"
#include "Delay.h"

DumpCube::DumpCube() {
	AddSequential(new BucketTiltPosition(200));  // 200 is selecto dump
	AddSequential(new Delay(0.5));
	AddSequential(new BucketTiltPosition(-6));  // Back to home  %rod15


}
