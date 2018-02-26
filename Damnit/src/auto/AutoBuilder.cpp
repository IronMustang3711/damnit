//
// Created by Jason Markham on 2/15/18.
//

#include <llvm/raw_ostream.h>
#include "AutoBuilder.h"
#include "FieldModel.h"
#include "SwitchAutos.h"
#include "ScaleAutos.h"
#include "MotionProfileExecutors.h"

AutoBuilder::AutoBuilder() : frc::InstantCommand("auto builder") {

}

void AutoBuilder::Initialize() {
    auto& f = FieldModel::getInstance();

    if(!f.fieldLayoutIsValid()){
        DriverStation::ReportError("invalid field layout!");
        return;
    }

    auto layout = f.getFieldLayout();
    auto start = f.getStartPosition();
    auto alliance = f.getAlliance();
    auto target = f.getAutoTarget();

    llvm::outs() << "autobuilder{layout=" << layout
                 << " start=" << start
                 <<"target="<< target
                 <<" alliance=" << alliance
                 << "}\n";

    Command* command;

      switch(start){

          case StartPosition::TOP: command = leftStartingPoint(std::get<0>(layout),std::get<1>(layout));
              break;
          case StartPosition::MIDDLE: command = centerStartingPoint(std::get<0>(layout));
              break;
          case StartPosition::BOTTOM: command =rightStartingPoint(std::get<0>(layout),std::get<1>(layout));
              break;
      }

    SmartDashboard::PutString("auto decision",command != nullptr ? command->GetName() : "null?!");
}

Command *AutoBuilder::centerStartingPoint(TargetLocation switchLocation) {
    switch (switchLocation){
        case TargetLocation::INVALID: return nullptr; //TODO! <--
        case TargetLocation::LEFT:return new CLSwitchAuto ;
        case TargetLocation::RIGHT:return new CRSwitchAuto;
    }
}

Command *AutoBuilder::leftStartingPoint(TargetLocation switchLocation, TargetLocation scaleLocation) {
    if(scaleLocation == TargetLocation::LEFT) return new LLScaleAuto;
    else if(switchLocation == TargetLocation::LEFT) return new LLSwitchAuto;
    else return new LFwd;
}

Command *AutoBuilder::rightStartingPoint(TargetLocation switchLocation, TargetLocation scaleLocation) {
    if(scaleLocation == TargetLocation::RIGHT) return new RRScaleAuto;
    else if(switchLocation == TargetLocation::LEFT) return new RRScaleAuto;
    else return new RFwd;
}


