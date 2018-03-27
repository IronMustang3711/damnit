//
// Created by Jason Markham on 3/27/18.
//

#include <fstream>
#include "RobotConfig.h"

RobotConfig::RobotConfig() {
/*
 * setup:
 *
 * ssh lvuser@roboRIO-3711-frc.local
 * no password.
 *
lvuser@roboRIO-3711-FRC:~$ pwd
/home/lvuser
lvuser@roboRIO-3711-FRC:~$ echo "PROTO" > robot_name

 */
        std::ifstream robot_name_ifs("/home/lvuser/robot_name");
        std::string name;
        robot_name_ifs >> name;
        if(name == "PROTO") isCompetition = false;

}

bool RobotConfig::IsCompetitionRobot() {
    static RobotConfig conf;
    return conf.isCompetition;
}
