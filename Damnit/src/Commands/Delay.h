#ifndef Delay_H
#define Delay_H

#include "Commands/TimedCommand.h"


class Delay : public frc::TimedCommand {
public:
	Delay(double timeout);
	void Initialize();
	void Execute();
	void End();
	void Interrupted();
};

#endif  // Delay_H
