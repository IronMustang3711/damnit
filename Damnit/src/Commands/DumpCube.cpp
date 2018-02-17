#include "DumpCube.h"
#include "bucketTiltPosition.h"
#include "UpperTiltPosition.h"
#include "Delay.h"
using namespace commands;
DumpCube::DumpCube() : frc::CommandGroup("Dump Cube") {
	AddSequential(Buckets::getInstance().auto_dump()); //(new BucketTiltPosition(200));  // 200 is selecto dump
	AddSequential(new Delay(0.5));
	AddSequential(Buckets::getInstance().to_home_tweak(-20));//(new BucketTiltPosition(-20));  // Back to home


}
