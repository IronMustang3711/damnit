//
// Created by Jason Markham on 2/27/18.
//

#include <SmartDashboard/SmartDashboard.h>
#include <DriverStation.h>
#include "AutoSelector.h"
#include "DontDoAnything.h"
#include "MotionProfileExecutors.h"
#include "SwitchAutos.h"
#include "ScaleAutos.h"
#include <networktables/NetworkTableInstance.h>

using namespace frc;
using namespace std;
AutoSelector::AutoSelector() {
    chooser.SetName("robot start position");
    chooser.AddDefault("center","center");
    chooser.AddObject("left","left");
    chooser.AddObject("right","right");

    SmartDashboard::PutData(&chooser);

    //    autoTable = nt::NetworkTableInstance::GetDefault().GetTable("SmartDashboard")->GetSubTable("Auto Modes");
    //    autoTable->Delete("options");
    //    nt::NetworkTableInstance::GetDefault().Flush();

   // auto selectedEntry = autoTable->GetEntry("selected");

}

frc::Command *AutoSelector::getCommand() {
    string msg = DriverStation::GetInstance().GetGameSpecificMessage();
    DriverStation::ReportWarning("msg="+msg);
    bool valid = messageIsValid(msg);
    if (!valid)
        return new DontDoAnything;


    bool enableScaleAuto = Preferences::GetInstance()->GetBoolean("auto.scale.enable",false);
    bool enableOppositeScaleAuto = Preferences::GetInstance()->GetBoolean("auto.scale.opposite.enable",false);


    string startPosition = nt::NetworkTableInstance::GetDefault()
            .GetTable("SmartDashboard")
            ->GetSubTable("robot start position")
            ->GetEntry("selected")
            .GetString("none");

    DriverStation::ReportWarning("start position="+startPosition);

    Command* ret=nullptr;

    if(startPosition == "left"){
        if(msg[0] == 'L'){
            ret = new LLSwitchAuto();
        }
        else if(msg[1]=='L' && enableScaleAuto){
            ret = new LLScaleAuto();
        }
        else if(msg[1]=='R' && enableOppositeScaleAuto){
            ret = new LRScaleAuto();
        }
        else{
            ret = new LFwd();
        }
    }
    else if(startPosition == "right"){
        if(msg[0] == 'R'){
            ret = new RRSwitchAuto();
        }
        else if(msg[1] == 'R' && enableScaleAuto){
            ret = new RRScaleAuto();
        }
        else if(msg[1]=='L' && enableOppositeScaleAuto){
           ret = new RLScaleAuto();
        }
        else {
            ret = new RFwd();

        }
    }
    else if(startPosition == "center"){
        if(msg[0] == 'L'){
            ret = new CLSwitchAuto();
        }
        else if(msg[0] == 'R') {
            ret = new CRSwitchAuto();
        }
    }

    if(ret == nullptr)
        ret = new DontDoAnything();

    DriverStation::ReportWarning("chosen="+ret->GetName());

    return ret;

}
// message must consist only of the characters 'L' & 'R' and have a length of 3
bool AutoSelector::messageIsValid(const std::string &msg) {
    if (msg.size() != 3){
        DriverStation::ReportWarning("invalid message(size) : "+msg);
        return false;
    }
    for (int i = 0; i<3;i++){
        if (msg[i] != 'R' && msg[i] != 'L'){
            DriverStation::ReportWarning("invalid message(char, ["+to_string(i)+"]="+to_string(msg[i])+"): "+msg);
            return false;
        }

    }
    return true;

}
