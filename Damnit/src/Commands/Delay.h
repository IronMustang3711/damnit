#ifndef Delay_H
#define Delay_H

#include <Commands/TimedCommand.h>

//Todo: remove: this is already implemented in wpilib Commands/WaitCommand
class Delay : public frc::TimedCommand {
public:
	explicit Delay(double timeout);
	void Initialize() override;
	void Execute() override;
	void End() override;
	void Interrupted() override;
};

#endif  // Delay_H
