//
// Created by Jason Markham on 2/13/18.
//

#include <Robot.h>
#include "Spin.h"

Spin::Spin() : TimedCommand("Spin", 1.0) {
    Requires(Robot::chassis.get());

}

void Spin::Execute() {
    Robot::chassis->ArcadeDrive(0.0, 0.9);
}
