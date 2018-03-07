#include "ReaderBoard.h"
#include "DumpCube.h"
#include "BucketTiltPosition.h"
#include "UpperTiltPosition.h"
#include "Delay.h"
DumpCube::DumpCube() : frc::CommandGroup("Dump Cube") {
	AddSequential(new BucketTiltAutoDump(),1.0); //(new BucketTiltPosition(200));  // 200 is selecto dump
	//AddSequential(new Delay(0.5));
	AddSequential(new BucketTiltAllTheWayBack());//(new BucketTiltPosition(-20));  // Back to home


}

void DumpCube::Initialize() {
	CommandGroup::Initialize();
	ReaderBoard::reportDump();
}
