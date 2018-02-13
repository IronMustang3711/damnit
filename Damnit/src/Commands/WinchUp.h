#ifndef WinchUp_H
#define WinchUp_H


#include "Commands/Command.h"

class WinchUp: public frc::Command {
public:
	WinchUp();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // WinchUp_H
