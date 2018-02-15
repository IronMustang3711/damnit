//
// Created by Jason Markham on 2/15/18.
//

#include <llvm/raw_ostream.h>
#include "AutoBuilder.h"
#include "FieldModel.h"

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

            //TODO!!!



}
