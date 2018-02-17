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

         Command* to_switch();
         Command* to_cube();
         Command* to_bucket();
         Command* to_home();

        static ClampTilts& getInstance();

    };
    class Clamps {
        const RobotConfig& config;
    public:
        explicit Clamps(const RobotConfig& config);
        Command* open();
        Command* close();
        Command* toggle();
        static Clamps& getInstance();

        Command *to_home();

        Command *to_switch();
    };
    class Buckets{
        const RobotConfig& config;
    public:
        explicit Buckets(const RobotConfig& config);
        Command* to_home();
        Command* to_home_tweak(double setpoint);
        Command* to_switch();
        Command* auto_level();
        Command* auto_dump();
        static Buckets& getInstance();

        Command *to_zero();

        Command *to_scale();
    };
}


#endif //DAMNIT_COMMANDFACTORY_H
