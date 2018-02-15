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

    TOP,MIDDLE,BOTTOM
};
enum class Target {
    SWITCH=0,
    SCALE,
    OPPOSING_SWITCH
};
enum class TargetLocation {
    INVALID,
    TOP = 1,
    BOTTOM,
    LEFT = static_cast<std::underlying_type_t<TargetLocation>>(TargetLocation::TOP),
    RIGHT = static_cast<std::underlying_type_t<TargetLocation>>(TargetLocation::BOTTOM)
};

enum class Alliance {
   // INVALID = 0,
    RED,BLUE
};

TargetLocation parse_TargetLocation(char c){
    switch(c){
        case 'L' : return TargetLocation::LEFT;
        case 'R' : return TargetLocation::RIGHT;
        default  : return TargetLocation::INVALID;
    }
}

typedef std::tuple<TargetLocation, TargetLocation, TargetLocation> FieldLayout;

FieldLayout
parse_field_layout_message(const std::string &message = frc::DriverStation::GetInstance().GetGameSpecificMessage()) {
    return (message.empty()) ?
           std::make_tuple(TargetLocation::INVALID,
                           TargetLocation::INVALID,
                           TargetLocation::INVALID)
                             : std::make_tuple(parse_TargetLocation(message.at(0)),
                                               parse_TargetLocation(message.at(1)),
                                               parse_TargetLocation(message.at(2)));

}

struct FieldModel {

    SendableChooser<Alliance> allianceChooser;
    SendableChooser<StartPosition> startChooser;


    std::string getFieldLayoutMessage(){
        //TODO frc::DriverStation::GetGameSpecificMessage();
        return SmartDashboard::GetString("FIELD","");
    }
    FieldLayout getFieldLayout(){return parse_field_layout_message(getFieldLayoutMessage());}

    bool fieldLayoutIsValid(){return std::get<0>(getFieldLayout()) != TargetLocation::INVALID;}


    FieldModel(){
        allianceChooser.SetName("Robot","Alliance");
        allianceChooser.AddDefault("red", Alliance::RED);
        allianceChooser.AddObject("blue",Alliance::BLUE);

        startChooser.SetName("Robot","Start Position");
        startChooser.AddDefault("bottom",StartPosition::BOTTOM);
        startChooser.AddObject("middle",StartPosition::MIDDLE);
        startChooser.AddObject("top",StartPosition::TOP);

        SmartDashboard::PutData(&allianceChooser);
        SmartDashboard::PutData(&startChooser);

        auto sd_table = nt::NetworkTableInstance::GetDefault().GetTable("SmartDashboard");

        sd_table->GetSubTable(allianceChooser.GetName())
                ->AddEntryListener("selected",
                                   [](NetworkTable* ,
                                      llvm::StringRef ,
                                      nt::NetworkTableEntry,
                                      std::shared_ptr<nt::Value> value,
                                      int ){
                                       llvm::outs() << "alliance chooser updated: "<<value->GetString() <<'\n';
                                   },
                                   nt::EntryListenerFlags::kUpdate);




        SmartDashboard::SetDefaultString("FIELD","LRL");

        sd_table->GetEntry("FIELD").AddListener([](const nt::EntryNotification& event){
          auto value =  event.value->GetString();
            llvm::outs() << "FIELD(ENTRY): "
                         << value
                         << "valid? = "
                         <<  (std::get<0>(parse_field_layout_message(value))
                              != TargetLocation::INVALID)
                         << '\n';

        },nt::EntryListenerFlags::kUpdate);

        sd_table->AddEntryListener("FIELD",[](NetworkTable*,
                                              llvm::StringRef,
                                              nt::NetworkTableEntry,
                                              std::shared_ptr<nt::Value> value,
                                              int){
                                       llvm::outs() << "FIELD: "
                                                    << value->GetString()
                                                    << "valid? = "
                                                    <<  (std::get<0>(parse_field_layout_message(value->GetString()))
                                                         != TargetLocation::INVALID)
                                                    << '\n';
                                   },
                                   nt::EntryListenerFlags::kUpdate);
    }

};
