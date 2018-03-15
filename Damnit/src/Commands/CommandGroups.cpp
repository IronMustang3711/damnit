////
//// Created by Jason Markham on 3/14/18.
////
//
//#pragma once
//
//
//#include <Commands/CommandGroup.h>
//
//
//
//inline
//frc::CommandGroup& operator << (frc::CommandGroup& group, frc::Command& cmd){ group.AddSequential(&cmd); return group;}
//
//inline
//frc::CommandGroup* operator || (frc::CommandGroup* group,frc::Command* cmd){group->AddParallel(cmd); return group; }
//
//
//
