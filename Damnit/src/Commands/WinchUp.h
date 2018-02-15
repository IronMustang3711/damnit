#ifndef WinchUp_H
#define WinchUp_H


#include "Commands/Command.h"

class WinchUp: public frc::Command {
public:
	WinchUp();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // WinchUp_H
