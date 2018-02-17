//
// Created by Jason Markham on 2/17/18.
//

#ifndef DAMNIT_COMMANDFACTORY_H
#define DAMNIT_COMMANDFACTORY_H


#include <Commands/Command.h>
#include "RobotConfig.h"
namespace commands {
    class ClampTilts {
        const RobotConfig& config;
    public:
        explicit ClampTilts(const RobotConfig& config);

         frc::Command* to_switch();
         frc::Command* to_cube();
         frc::Command* to_bucket();
         frc::Command* to_home();

        static ClampTilts& getInstance();

    };
    class Clamps {
        const RobotConfig& config;
    public:
        explicit Clamps(const RobotConfig& config);
        frc::Command* open();
        frc::Command* close();
        frc::Command* toggle();
        static Clamps& getInstance();

        frc::Command *to_home();

        frc::Command *to_switch();
    };
    class Buckets{
        const RobotConfig& config;
    public:
        explicit Buckets(const RobotConfig& config);
        frc::Command* to_home();
        frc::Command* to_home_tweak(double setpoint);
        frc::Command* to_switch();
        frc::Command* auto_level();
        frc::Command* auto_dump();
        static Buckets& getInstance();

        frc::Command *to_zero();

        frc::Command *to_scale();
        frc::Command* winch_prep();
    };
}


#endif //DAMNIT_COMMANDFACTORY_H
