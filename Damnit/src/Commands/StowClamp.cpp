#include "StowClamp.h"
#include "ClampPosition.h"
#include "ClampTiltPosition.h"

StowClamp::StowClamp() : frc::CommandGroup("Stow Clamp") {
	AddSequential(new ClampPosition(152));  // Open Clamp %rod15
	AddSequential(new ClampTiltPosition(0));  // stow below
}
