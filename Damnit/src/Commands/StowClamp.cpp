#include "StowClamp.h"
#include "ClampPosition.h"
#include "ClampTiltPosition.h"

StowClamp::StowClamp() {
	AddSequential(new ClampPosition(220));  // Open Clamp
	AddSequential(new ClampTiltPosition(0));  // stow below
}
