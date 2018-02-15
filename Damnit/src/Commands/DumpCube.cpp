#include "DumpCube.h"
#include "bucketTiltPosition.h"
#include "UpperTiltPosition.h"
#include "Delay.h"

DumpCube::DumpCube() : frc::CommandGroup("Dump Cube") {
	AddSequential(new BucketTiltPosition(200));  // 200 is selecto dump
	AddSequential(new Delay(0.5));
	AddSequential(new BucketTiltPosition(-20));  // Back to home


}
