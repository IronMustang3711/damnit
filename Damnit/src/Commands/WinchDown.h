#ifndef WinchDown_H
#define WinchDown_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class WinchDown: public frc::Command {
public:
	WinchDown();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // WinchDown_H
