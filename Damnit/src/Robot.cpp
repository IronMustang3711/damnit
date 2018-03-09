// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// 28-jan-18 rod
// adjusted p and tolerance
// changed x to z in drive joystick
//
#include <CameraServer.h>
#include <Commands/Scheduler.h>
#include <RobotBase.h>
#include "Robot.h"

#include <ntcore.h>
#include <networktables/NetworkTableInstance.h>
#include <networktables/EntryListenerFlags.h>
#include <llvm/raw_ostream.h>
#include <llvm/ArrayRef.h>
#include <fstream>
#include <string>
#include "ReaderBoard.h"
#include "auto/AutoSelector.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<UpperTilt> Robot::upperTilt;
std::shared_ptr<Bucket> Robot::bucket;
std::shared_ptr<ClampTilt> Robot::clampTilt;
std::shared_ptr<Chassis> Robot::chassis;
std::shared_ptr<Clamp> Robot::clamp;
std::unique_ptr<OI> Robot::oi;

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<Winch> Robot::winch;

bool Robot::isCompetitionRobot = true;

void Robot::RobotInit() {
/*
 * setup:
 *
 * ssh lvuser@roboRIO-3711-frc.local
 * no password.
 *
lvuser@roboRIO-3711-FRC:~$ pwd
/home/lvuser
lvuser@roboRIO-3711-FRC:~$ echo "PROTO" > robot_name

 */
    {
        std::ifstream robot_name_ifs("/home/lvuser/robot_name");
        std::string name;
        robot_name_ifs >> name;
        if(name == "PROTO") Robot::isCompetitionRobot = false;
        SmartDashboard::PutString("robot",Robot::isCompetitionRobot ? "competition" : "prototype");
    }
    RobotMap::init();
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    upperTilt.reset(new UpperTilt());
    bucket.reset(new Bucket());
    clampTilt.reset(new ClampTilt());
    chassis.reset(new Chassis());
    clamp.reset(new Clamp());
    winch.reset(new Winch());

    commands = new Commands();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    // This MUST be here. If the OI creates Commands (which it very likely
    // will), constructing it during the construction of CommandBase (from
    // which commands extend), subsystems are not guaranteed to be
    // yet. Thus, their requires() statements may grab null pointers. Bad
    // news. Don't move it.
    oi = std::make_unique<OI>(commands);

   autoSelector = std::make_unique<AutoSelector>();

   // initAutoChooser();








    //NOTE: camera stream choppyness seems to be a computer issue rather than a roborio or SmartDashboard issue.
    // the camera stream is smooth on my computer
    auto cam = CameraServer::GetInstance()->StartAutomaticCapture();
    cam.SetResolution(160, 120);
    cam.SetFPS(30);



    //frc::SmartDashboard::PutData(RobotMap::subsystem1PowerDistributionPanel1.get());
    //frc::SmartDashboard::PutData(RobotMap::ahrs.get());

    ReaderBoard::reportInit();


}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit() {
    Robot::bucket->Disable();
    Robot::upperTilt->Disable();
    Robot::clampTilt->Disable();
    Robot::clamp->Disable();
    if (autonomousCommand != nullptr)
        autonomousCommand->Cancel();

    ReaderBoard::reportDisabled();
}

void Robot::DisabledPeriodic() {
    frc::Scheduler::GetInstance()->Run();


    if (RobotController::GetUserButton()) {
        Robot::clamp->reset();
        Robot::clampTilt->reset();
        Robot::upperTilt->reset();
        Robot::bucket->reset();
        Robot::chassis->resetEncoders();
    }
}

void Robot::AutonomousInit() {
    // Robot::chassis->prepareForAutonomous();
    llvm::outs() << "starting auto\n";
    ReaderBoard::reportAuto();


    autonomousCommand = autoSelector->getCommand();//getAutoCommand();
//     autonomousCommand = DriveForward;


    if (autonomousCommand != nullptr) {
        autonomousCommand->Start();
        DriverStation::ReportWarning("starting auto command: " + autonomousCommand->GetName());
        ReaderBoard::reportAutoName(autonomousCommand->GetName());
    } else {
        DriverStation::ReportError("null auto command!");
    }

}

void Robot::AutonomousPeriodic() {
    frc::Scheduler::GetInstance()->Run();
}

void Robot::TeleopInit() {
    Robot::chassis->prepareForTeleop();
    if (autonomousCommand != nullptr)
        autonomousCommand->Cancel();
    ReaderBoard::reportTeleop();
    updateAllianceColor();
}

void Robot::TeleopPeriodic() {

    frc::Scheduler::GetInstance()->Run();
}


void Robot::TestPeriodic() {
    Robot::chassis->testPeriodic();
}




void Robot::TestInit() {
    //Robot::chassis->enableInductiveBreaking(false);

}

void Robot::RobotPeriodic() {

    SmartDashboard::PutNumber("Upper", Robot::upperTilt->GetPosition());
    SmartDashboard::PutNumber("Bucket", Robot::bucket->GetPosition());
    SmartDashboard::PutNumber("Lower", Robot::clampTilt->GetPosition());
    SmartDashboard::PutNumber("Clamp", Robot::clamp->GetPosition());

}

void Robot::updateAllianceColor() {
	switch (DriverStation::GetInstance().GetAlliance()){
	case DriverStation::kRed:
		RobotMap::lightsRed->Set(true);
		RobotMap::lightsGreen->Set(false);
		RobotMap::lightsBlue->Set(false);

		break;
	case DriverStation::kBlue:
		RobotMap::lightsBlue->Set(true);
		RobotMap::lightsGreen->Set(false);
		RobotMap::lightsRed->Set(false);

		break;
	case DriverStation::kInvalid:
		RobotMap::lightsGreen->Set(true);

		break;


	}
}

//void Robot::initAutoChooser() {
//    llvm::outs() << "initAutoChooser\n";
//
//
//
//    std::vector<Command*> as {
//            new Straight_10ft,
//            new RRSwitch,
//            new RRSwitchAuto,
//            new RRScale,
//            new RRScaleAuto,
//            new CRSwitch,
//            new CRSwitchAuto,
//            new CLSwitch,
//            new CLSwitchAuto,
//            new LLSwitch,
//            new LLSwitchAuto,
//            new LLScale,
//            new LLScaleAuto,
//            new LFwd,
//            new RFwd,
//            new RLScale,
//            new RLScaleAuto,
//
//    };
//    for(auto a : as){
//      autos[a->GetName()] = a;
//    }
//
//    //autos = {
//           // {"straight 10ft", new Straight_10ft()},
//
//
////            {"don't do anything", do_nothing},
////            {"drive forward(timed)", auto_dumbFwd},
////            {"simple auto sequence", auto_seq},
////            {"drive forward(gyro+encoder)", auto_fwd_ge},
////            {"drive forward(profiled)", auto_fwd_mm},
////            {"emotion profile(right)", auto_profiled},
////            {"right hook", right_hook},
////            {"right hook to scale", right_to_scale}
//
//   // };
//
////
//    for (const auto &elem : autos) {
//        SmartDashboard::PutData(elem.second);
//    }
//
//    keys.clear();
//    keys.reserve(autos.size());
//    for (const auto &it : autos) {
//        keys.push_back(it.first);
//    }
//
//    autoTable = nt::NetworkTableInstance::GetDefault().GetTable("SmartDashboard")->GetSubTable("Auto Modes");
//    autoTable->Delete("options");
//    nt::NetworkTableInstance::GetDefault().Flush();
//
//    autoTable->PutString(".type", "String Chooser");
//    autoTable->PutString(".name", "Auto Chooser!!");
//
//    autoTable->PutStringArray("options", keys);
//
//    autoTable->PutString("default", autos.begin()->first);
//    // autoTable->PutString("selected", autos.begin()->first);
//
//    //		autoTable->GetEntry("selected").AddListener([this](const nt::EntryNotification& note){
////				llvm::outs() << "selected: "<<note.value->GetString() << " flags: " << note.flags <<'\n';
////				m_autonomousCommand = autos.at(note.value->GetString());
////		}, 0xff);
//}
//
//frc::Command *Robot::getAutoCommand() {
//    auto selectedEntry = autoTable->GetEntry("selected");
//
//    return autos.at(selectedEntry.GetString(autos.begin()->first));
//
//}




START_ROBOT_CLASS(Robot)


