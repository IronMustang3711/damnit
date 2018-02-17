//
// Created by Jason Markham on 2/17/18.
//

#include <Robot.h>
#include "CommandFactory.h"
#include "ClampTiltPosition.h"
#include "ClampPosition.h"
#include "UpperTiltPosition.h"
#include "BucketTiltPosition.h"

Command *commands::ClampTilts::to_switch() {
    return new ClampTiltPosition(config.clamp_tilt.switch_setpoint);
}

Command *commands::ClampTilts::to_cube() {
     return new ClampTiltPosition(config.clamp_tilt.cube_setpoint);;
}

Command *commands::ClampTilts::to_bucket() {
    return new ClampTiltPosition(config.clamp_tilt.bucket_setpoint);
}


Command *commands::Clamps::open() {
    return new ClampPosition(0,config.clamp.open_threshold);
}

Command *commands::Clamps::close() {
    return new ClampPosition(config.clamp.open_setpoint,config.clamp.open_threshold);
}
Command *commands::Buckets::to_home() {
    return new BucketTiltPosition(config.bucket_tilt.home_setpoint);
}


commands::ClampTilts::ClampTilts(const RobotConfig & _config) : config(_config)  {
}

commands::Clamps::Clamps(const RobotConfig &c) : config(c) {
}
commands::Buckets::Buckets(const RobotConfig &c) : config(c) {
}

commands::Buckets &commands::Buckets::getInstance() {
    static Buckets inst(Robot::config);
    return inst;
}

Command *commands::Buckets::auto_level() {
    return new BucketTiltPosition(100);
}

Command *commands::Buckets::auto_dump() {
    return new BucketTiltPosition(200);
}

Command *commands::Buckets::to_home_tweak(double setpoint) {
    return new BucketTiltPosition(setpoint);
}

Command *commands::Buckets::to_switch() {
    return new BucketTiltPosition(150);
}

Command *commands::Buckets::to_zero() {
    return new BucketTiltPosition(0);
}

Command *commands::Buckets::to_scale() {
    return new BucketTiltPosition(205);
}

commands::ClampTilts &commands::ClampTilts::getInstance() {
    static ClampTilts inst(Robot::config);
    return inst;
}

Command *commands::ClampTilts::to_home() {
    return new ClampTiltPosition(0);
}

commands::Clamps &commands::Clamps::getInstance() {
    static Clamps inst(Robot::config);
    return inst;
}

Command *commands::Clamps::toggle() {
    return new ClampPosition(-1,config.clamp.open_threshold);
}

Command *commands::Clamps::to_home() {
    return new ClampPosition(config.clamp.to_home,config.clamp.open_threshold);
}

Command *commands::Clamps::to_switch() {
    return new ClampPosition(config.clamp.to_switch,config.clamp.to_switch);
}
