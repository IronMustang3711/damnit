//
// Created by Jason Markham on 2/16/18.
//
#pragma once



struct RobotConfig {

    enum Robot {
        PRODUCTION,
        PROTOTYPE
    };

        struct Clamp {
            double open_setpoint;
            double open_threshold;
            double to_home;
            double to_switch;
        };
         Clamp clamp;

        struct ClampTilt {
            double cube_setpoint;
            double bucket_setpoint;
            double switch_setpoint;
        };
        ClampTilt clamp_tilt;

        struct BucketTilt {
            double home_setpoint;
            double winch_prep;
        };
        BucketTilt bucket_tilt;


    struct DriveTrain {
        double rotation_offset_multiplier;
    };
    DriveTrain driveTrain;
};

extern RobotConfig ProductionConfig;
extern RobotConfig PrototypeConfig;


