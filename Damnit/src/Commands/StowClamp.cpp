#include "StowClamp.h"
#include "ClampPosition.h"
#include "ClampTiltPosition.h"

StowClamp::StowClamp() : frc::CommandGroup("Stow Clamp") {
	AddSequential(commands::Clamps::getInstance().open());//(new ClampPosition(220));  // Open Clamp
	AddSequential(commands::ClampTilts::getInstance().to_home());//(new ClampTiltPosition(0));  // stow below
}
