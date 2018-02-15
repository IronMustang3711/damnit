/*
 * ToggleBreaking.h
 *
 *  Created on: Feb 14, 2018
 *      Author: jason
 */

#pragma once
#include <Commands/InstantCommand.h>
class ToggleBreaking : public frc::InstantCommand {
public:
	ToggleBreaking();

protected:
	void Execute() override;
	bool enable = true;
};

