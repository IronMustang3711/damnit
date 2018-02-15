//
// Created by Jason Markham on 2/15/18.
//

#pragma once

#include <type_traits>
#include <tuple>
#include <networktables/EntryListenerFlags.h>
#include <networktables/NetworkTableInstance.h>
#include <DriverStation.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>

/*
 * see http://wpilib.screenstepslive.com/s/currentCS/m/getting_started/l/826278-2018-game-data-details
 *
 * Data regarding plate assignment is provided to each robot based on their alliance. In other words,
 * the Blue alliance will receive data corresponding to the location of the Blue plates and the Red alliance
 * will receive data corresponding to the location of the Red plates. The data is referenced from the perspective
 * of the Drive Team looking out from their Player Station. The data consists of three characters, each 'L' or 'R',
 * representing the location (Left or Right) of the Alliance's plate on each element,
 * starting with the element closest to the Alliance.
 *
 */


enum class StartPosition {
    TOP,
    MIDDLE,
    BOTTOM
};

enum class AutoTarget {
    NONE = 0,
    LINE,
    SWITCH,
    SCALE
};
enum class TargetLocation {
    INVALID,
    TOP = 1,
    BOTTOM,

    LEFT = static_cast<std::underlying_type_t<TargetLocation>>(TargetLocation::TOP),
    RIGHT = static_cast<std::underlying_type_t<TargetLocation>>(TargetLocation::BOTTOM)
};

enum class Alliance {
    RED,
    BLUE
};


typedef std::tuple<TargetLocation, TargetLocation> FieldAutoLayout;



std::string to_string(StartPosition p);
std::string to_string(TargetLocation l, bool use_top_bottom = true);
std::string to_string(Alliance a);
std::string to_string(FieldAutoLayout l);


TargetLocation parse_TargetLocation(char c);
FieldAutoLayout
parse_field_layout_message(const std::string &message = frc::DriverStation::GetInstance().GetGameSpecificMessage());

struct FieldModel {

    SendableChooser<Alliance> allianceChooser;
    SendableChooser<StartPosition> startChooser;
    SendableChooser<AutoTarget> targetChooser;


    std::string getFieldLayoutMessage();
    FieldAutoLayout getFieldLayout();

    bool fieldLayoutIsValid();

    StartPosition getStartPosition();

    Alliance getAlliance();

    FieldModel();

    void update();

};
