#include "DumpCube.h"
#include "BucketTiltPosition.h"
#include "UpperTiltPosition.h"
#include "Delay.h"
DumpCube::DumpCube() : frc::CommandGroup("Dump Cube") {
	AddSequential(new BucketTiltAutoDump()); //(new BucketTiltPosition(200));  // 200 is selecto dump
	AddSequential(new Delay(0.5));
	AddSequential(new BucketTiltToHome());//(new BucketTiltPosition(-20));  // Back to home


}
