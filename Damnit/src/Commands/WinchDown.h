#ifndef WinchDown_H
#define WinchDown_H


#include "Commands/Command.h"



class WinchDown: public frc::Command {
public:
	WinchDown();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End() override;
	void Interrupted() override;
};

#endif  // WinchDown_H
