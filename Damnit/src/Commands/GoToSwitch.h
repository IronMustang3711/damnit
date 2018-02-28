#ifndef GoToSwitch_H
#define GoToSwitch_H

#include <Commands/CommandGroup.h>

class GoToSwitch : public frc::CommandGroup {
public:
	GoToSwitch();

protected:
	void Initialize() override ;
};

#endif  // GoToSwitch_H
