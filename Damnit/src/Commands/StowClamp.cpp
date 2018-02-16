#include "StowClamp.h"
#include "Commands/ClampPosition.h"
#include "Commands/ClampTiltPosition.h"

StowClamp::StowClamp() {
	AddSequential(new ClampPosition(152));  // Open Clamp %rod15
	AddSequential(new ClampTiltPosition(0));  // stow below
}
