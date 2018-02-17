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
#include <auto/AutoBuilder.h>
#include <auto/DontDoAnything.h>
#include <auto/DriveForward.h>
#include "auto/FieldModel.h"
#include "Robot.h"

#include <ntcore.h>
#include <networktables/NetworkTableInstance.h>
#include <networktables/EntryListenerFlags.h>
#include <llvm/raw_ostream.h>
#include <llvm/ArrayRef.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<UpperTilt> Robot::upperTilt;
std::shared_ptr<Bucket> Robot::bucket;
std::shared_ptr<ClampTilt> Robot::clampTilt;
std::shared_ptr<Chassis> Robot::chassis;
std::shared_ptr<Clamp> Robot::clamp;
std::unique_ptr<OI> Robot::oi;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<Winch> Robot::winch;
RobotConfig Robot::config;





void Robot::RobotInit() {
    config = ProductionConfig; //TODO!

	RobotMap::init();
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    upperTilt.reset(new UpperTilt());
    bucket.reset(new Bucket());
    clampTilt.reset(new ClampTilt());
    chassis.reset(new Chassis(config.driveTrain.rotation_offset_multiplier));
    clamp.reset(new Clamp());
    winch.reset(new Winch());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi = std::make_unique<OI>();

    initAutoChooser();

    FieldModel::getInstance();






    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS

	CameraServer::GetInstance()->StartAutomaticCapture().SetResolution(320,
	240);  // %rod3



	//frc::SmartDashboard::PutData(RobotMap::subsystem1PowerDistributionPanel1.get());
	frc::SmartDashboard::PutData(RobotMap::ahrs.get());


}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){
	Robot::bucket->Disable();
	Robot::upperTilt->Disable();
	Robot::clampTilt->Disable();
	Robot::clamp->Disable();
}

void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();


	if(RobotController::GetUserButton()){
		Robot::clamp->reset();
		Robot::clampTilt->reset();
		Robot::upperTilt->reset();
		Robot::bucket->reset();
		Robot::chassis->resetEncoders();
	}
}

void Robot::AutonomousInit() {
    Robot::chassis->prepareForAutonomous();
	llvm::outs() << "starting auto\n";

    autonomousCommand = getAutoCommand();


	if (autonomousCommand != nullptr){
		autonomousCommand->Start();
		DriverStation::ReportWarning("starting auto command: "+autonomousCommand->GetName());
	} else{
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
}

void Robot::TeleopPeriodic() {
	SmartDashboard::PutNumber("Upper", Robot::upperTilt->GetPosition());
	SmartDashboard::PutNumber("Bucket", Robot::bucket->GetPosition());
	SmartDashboard::PutNumber("Lower", Robot::clampTilt->GetPosition());
	SmartDashboard::PutNumber("Clamp", Robot::clamp->GetPosition());
	frc::Scheduler::GetInstance()->Run();
}


void Robot::TestPeriodic() {
	Robot::chassis->testPeriodic();
}


START_ROBOT_CLASS(Robot)

void Robot::TestInit() {
	//Robot::chassis->enableInductiveBreaking(false);

}

void Robot::RobotPeriodic() {
	//FieldModel::getInstance().update();

}

void Robot::initAutoChooser() {
    llvm::outs() <<"initAutoChooser\n";

    /*
     *
     *     DumbDriveForward* auto_dumbFwd;
//    AutoBuilder* auto_builder;
    AutonomousCommand* auto_seq;
    DriveForwardGyroEncoder* auto_fwd_ge;
    DriveForward* auto_fwd_mm;
    MotionProfileCommand* auto_profiled;
    DontDoAnything do_nothing;
     */
    auto_dumbFwd = new DumbDriveForward;
    auto_seq = new AutonomousCommand;
    auto_fwd_ge = new DriveForwardGyroEncoder;
    auto_fwd_mm = new DriveForward;
     auto_profiled = new MotionProfileCommand;
     do_nothing = new DontDoAnything;

    autos =  {
    		{"don't do anything",do_nothing },
    		{"drive forward(timed)", auto_dumbFwd},
        {"simple auto sequence",        auto_seq},
        {"drive forward(gyro+encoder)", auto_fwd_ge},
        {"drive forward(profiled)",     auto_fwd_mm},
        {"experimental switch auto(x)", auto_profiled}

    };


    for(const auto& elem : autos){
        SmartDashboard::PutData(elem.second);
    }

    keys.clear();
    keys.reserve(autos.size());
    for (const auto &it : autos) {
        keys.push_back(it.first);
    }

    autoTable = nt::NetworkTableInstance::GetDefault().GetTable("SmartDashboard")->GetSubTable("Auto Modes");
    autoTable->Delete("options");
    nt::NetworkTableInstance::GetDefault().Flush();

    autoTable->PutString(".type", "String Chooser");
    autoTable->PutString(".name", "Auto Chooser!!");

    autoTable->PutStringArray("options", keys);

    autoTable->PutString("default", autos.begin()->first);
    autoTable->PutString("selected", autos.begin()->first);

    //		autoTable->GetEntry("selected").AddListener([this](const nt::EntryNotification& note){
//				llvm::outs() << "selected: "<<note.value->GetString() << " flags: " << note.flags <<'\n';
//				m_autonomousCommand = autos.at(note.value->GetString());
//		}, 0xff);
}

frc::Command *Robot::getAutoCommand() {
    auto selectedEntry = autoTable->GetEntry("selected");

    return autos.at(selectedEntry.GetString(autos.begin()->first));

}




