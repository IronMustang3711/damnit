//
// Created by Jason Markham on 2/14/18.
//

#pragma once

#include <array>

namespace mp {

    constexpr double TIME_STEP = 0.01;

    struct Prof {
        double leftPosition;
        double leftVelocity;
        double rightPosition;
        double rightVelocity;
    };

    typedef std::array<Prof, 666> RIGHT_TO_SWITCH_PROFS_t;
    typedef std::array<Prof,809> RIGHT_TO_SCALE_PROFS_t;
//todo: constexpr
    extern RIGHT_TO_SWITCH_PROFS_t PROFS;

    extern RIGHT_TO_SCALE_PROFS_t RIGHT_HOOK_TO_SCALE;
}
