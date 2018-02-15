//
// Created by Jason Markham on 2/14/18.
//

#pragma once

#include <array>

namespace mp {

    constexpr double TIME_STEP = 0.001;

    struct Prof {
        double leftPosition;
        double leftVelocity;
        double rightPosition;
        double rightVelocity;
    };
//todo: constexpr
    extern std::array<Prof,757> PROFS;
}
