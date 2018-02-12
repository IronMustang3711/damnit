#include "StowClamp.h"
#include "Commands/ClampPosition.h"
#include "Commands/ClampTiltPosition.h"

StowClamp::StowClamp() {
	AddSequential(new ClampPosition(220));  // Open Clamp
	AddSequential(new ClampTiltPosition(0));  // stow below
}
