//
// Created by Jason Markham on 2/14/18.
//

#pragma once

#include <cinttypes>
#include <ctre/phoenix/Motion/TrajectoryPoint.h>
#include <array>
namespace mp {

    constexpr double TIME_STEP = 0.01;

    struct Prof {
        double leftPosition;
        double leftVelocity;
        double rightPosition;
        double rightVelocity;
    };

    struct PV{
        double position;
        double velocity;
    };
    template <ctre::phoenix::motion::TrajectoryDuration _duration>
    struct PVD : public PV {
        constexpr ctre::phoenix::motion::TrajectoryDuration getDuration() const{ return _duration;}

    };




    template<std::size_t LEN,ctre::phoenix::motion::TrajectoryDuration duration>
    struct Profs{
        std::array<PV,LEN> left;
        std::array<PV,LEN> right;
        constexpr ctre::phoenix::motion::TrajectoryDuration getDuration() const { return duration; }
    };
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
    static constexpr bool profCompileTest(){
       constexpr PVD<ctre::phoenix::motion::TrajectoryDuration_10ms> pvd{};
        static_assert(pvd.getDuration() == ctre::phoenix::motion::TrajectoryDuration_10ms,"10ms trajectory duration");

        constexpr Profs<1,ctre::phoenix::motion::TrajectoryDuration_10ms> profs{
                {PV{0.0,0.0}},
                {PV{0.0,0.0}}
        };

        static_assert(profs.getDuration() == ctre::phoenix::motion::TrajectoryDuration_10ms,"10ms trajectory duration");

        return true;
    }

#pragma GCC diagnostic pop



}
