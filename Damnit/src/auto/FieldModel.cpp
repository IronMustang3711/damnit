//
// Created by Jason Markham on 2/15/18.
//
#include <llvm/raw_ostream.h>
#include "FieldModel.h"
#pragma ide diagnostic ignored "DuplicateSwitchCase"

std::string to_string(StartPosition p) {
    switch (p){

        case StartPosition::TOP:return "top";
        case StartPosition::MIDDLE: return "middle";
        case StartPosition::BOTTOM: return "bottom";
        default: return "invalid";
    }
}

std::string to_string(TargetLocation l, bool use_top_bottom) {
    if(use_top_bottom){
        switch (l){
            case TargetLocation::TOP:return "top";
            case TargetLocation::BOTTOM:return "bottom";
            case TargetLocation::INVALID:
            default: return "invalid";

        }}
    else{
        switch(l){
            case TargetLocation::LEFT:return "left";
            case TargetLocation::RIGHT:return "right";
            case TargetLocation::INVALID:
            default: return "invalid";


        }
    }
}

std::string to_string(Alliance a) {
    switch(a){

        case Alliance::RED:return "red";
        case Alliance::BLUE:return "blue";
        default: return "invalid";

    }
}

std::string to_string(FieldAutoLayout l) {
    return "switch: "+to_string(std::get<0>(l))+ " scale: "+ to_string(std::get<1>(l));
}

TargetLocation parse_TargetLocation(char c) {
    switch(c){
        case 'L' : return TargetLocation::LEFT;
        case 'R' : return TargetLocation::RIGHT;
        default  : return TargetLocation::INVALID;
    }
}

FieldAutoLayout parse_field_layout_message(const std::string &message) {
    bool valid = message.size() == 3
                 &&  std::all_of(message.begin(),message.end(),[](auto c){return c == 'L' || c=='R';});

    return (valid) ?
           std::make_tuple(parse_TargetLocation(message.at(0)),
                           parse_TargetLocation(message.at(1)))
                   : std::make_tuple(TargetLocation::INVALID,
                                     TargetLocation::INVALID);


}

std::string to_string(AutoTarget t) {
    switch (t){
        case AutoTarget::NONE:return "none";
        case AutoTarget::LINE:return "line";
        case AutoTarget::SWITCH:return "switch";
        case AutoTarget::SCALE: return "scale";
        default: return "invalid";
    }
}

llvm::raw_ostream &operator<<(llvm::raw_ostream &os, const AutoTarget &a) {
    os << to_string(a);
    return os;
}

llvm::raw_ostream &operator<<(llvm::raw_ostream &os, const StartPosition &a) {
    os << to_string(a);
    return os;
}

llvm::raw_ostream &operator<<(llvm::raw_ostream &os, const TargetLocation &a) {
    os << to_string(a);
    return os;
}

llvm::raw_ostream &operator<<(llvm::raw_ostream &os, const FieldAutoLayout &l) {
    os << to_string(l);
    return os;
}

llvm::raw_ostream &operator<<(llvm::raw_ostream &os, const Alliance &a) {
    os << to_string(a);
    return os;
}

std::string FieldModel::getFieldLayoutMessage() {
    auto ds_msg = frc::DriverStation::GetInstance().GetGameSpecificMessage();
    return !ds_msg.empty() ?  ds_msg: SmartDashboard::GetString("FIELD",""); //TODO: remove when done testing
}

FieldAutoLayout FieldModel::getFieldLayout() {return parse_field_layout_message(getFieldLayoutMessage());}

bool FieldModel::fieldLayoutIsValid() {return std::get<0>(getFieldLayout()) != TargetLocation::INVALID;}

StartPosition FieldModel::getStartPosition() {
    auto ds_start = frc::DriverStation::GetInstance().GetLocation();
    switch (ds_start) {
        case 0: return StartPosition::BOTTOM;
        case 1: return StartPosition::MIDDLE;
        case 2: return StartPosition::TOP;
        default:
            DriverStation::ReportError("invalid start position");
            return StartPosition::BOTTOM;
    }
}

Alliance FieldModel::getAlliance() {
    auto ds_alliance = DriverStation::GetInstance().GetAlliance();
    switch(ds_alliance){
        case DriverStation::kBlue : return Alliance::BLUE;
        case DriverStation::kRed : return Alliance::RED;
        case DriverStation::kInvalid :
        default:
            DriverStation::ReportError("invalid alliance");
            return Alliance::BLUE;

    }
}

FieldModel::FieldModel() : frc::Subsystem("Field model") {
    allianceChooser.SetName("Robot","Alliance");
    allianceChooser.AddDefault("red", Alliance::RED);
    allianceChooser.AddObject("blue",Alliance::BLUE);

    startChooser.SetName("Robot","Start Position");
    startChooser.AddDefault("bottom",StartPosition::BOTTOM);
    startChooser.AddObject("middle",StartPosition::MIDDLE);
    startChooser.AddObject("top",StartPosition::TOP);

    targetChooser.SetName("Robot","Auto Target");
    targetChooser.AddDefault("none",AutoTarget::NONE);
    targetChooser.AddObject("line",AutoTarget::LINE);
    targetChooser.AddObject("switch",AutoTarget::SWITCH);
    targetChooser.AddObject("scale",AutoTarget::SCALE);

    SmartDashboard::PutData(&allianceChooser);
    SmartDashboard::PutData(&startChooser);
    SmartDashboard::PutData(&targetChooser);

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




  //  SmartDashboard::SetDefaultString("FIELD","LRL");

    sd_table->GetEntry("FIELD").AddListener([](const nt::EntryNotification& event){
        auto value =  event.value->GetString();
        SmartDashboard::PutBoolean("message valid", (std::get<0>(parse_field_layout_message(value))
                          != TargetLocation::INVALID));
//        llvm::outs() << "FIELD(ENTRY): "
//                     << value
//                     << "valid? = "
//                     <<  (std::get<0>(parse_field_layout_message(value))
//                          != TargetLocation::INVALID)
//                     << '\n';

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

void FieldModel::update() {
    SmartDashboard::PutBoolean("field message is valid", fieldLayoutIsValid());


    SmartDashboard::PutString("field message",getFieldLayoutMessage());
    SmartDashboard::PutString("alliance",to_string(getAlliance()));
    SmartDashboard::PutString("start position",to_string(getStartPosition()));
    SmartDashboard::PutString("target position",to_string(getFieldLayout()));

}

FieldModel &FieldModel::getInstance() {
    static FieldModel inst;
    return inst;
}

AutoTarget FieldModel::getAutoTarget() {
    return targetChooser.GetSelected();
}
