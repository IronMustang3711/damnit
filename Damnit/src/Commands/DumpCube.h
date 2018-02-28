#ifndef DumpCube_H
#define DumpCube_H

#include <Commands/CommandGroup.h>

class DumpCube : public frc::CommandGroup {
public:
	DumpCube();

protected:
	void Initialize() override ;
};

#endif  // DumpCube_H
