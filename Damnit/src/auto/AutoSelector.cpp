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

using namespace frc;
using namespace std;
AutoSelector::AutoSelector() {
    chooser.SetName("robot start position");
    chooser.AddDefault("center","center");
    chooser.AddObject("left","left");
    chooser.AddObject("right","right");

    SmartDashboard::PutData(&chooser);

}

frc::Command *AutoSelector::getCommand() {
    string msg = DriverStation::GetInstance().GetGameSpecificMessage();
    bool valid = messageIsValid(msg);
    if (!valid)
        return new DontDoAnything;


    bool enableScaleAuto = Preferences::GetInstance()->GetBoolean("auto.scale.enable",true);

    string startPosition = chooser.GetSelected();

    Command* ret=nullptr;

    if(startPosition == "left"){
        if(msg[0] == 'L'){
            ret = new LLSwitchAuto();
        }
        else if(msg[1]=='L' && enableScaleAuto){
            ret = new LLScaleAuto();
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
