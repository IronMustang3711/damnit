//
// Created by Jason Markham on 2/16/18.
//

#include "RobotConfig.h"

RobotConfig ProductionConfig {
        .clamp = {
                .open_setpoint = 152,
                .open_threshold = 100,
                .to_home = 84,
                .to_switch = 215
        },
        .clamp_tilt = {
                .cube_setpoint = 336,
                .bucket_setpoint = 82,
                .switch_setpoint = 206
        },

        .bucket_tilt = {
                .home_setpoint = -6,
                .winch_prep = 217
        },
        .driveTrain = {
                .rotation_offset_multiplier = -0.1
        }

};

RobotConfig PrototypeConfig = {
        .clamp  = {
                .open_setpoint = 220,
                .open_threshold = 200,
                .to_home = 82,
                .to_switch = 206
        },
        .clamp_tilt = {
                .cube_setpoint = 357,
                .bucket_setpoint = 82,
                .switch_setpoint = 215
        },

        .bucket_tilt = {
                .home_setpoint = -15,
                .winch_prep = 217
        },
        .driveTrain = {
                .rotation_offset_multiplier = 0.0
        }

};