
#include <llvm/raw_ostream.h>
#include <Commands/Command.h>
#include <SmartDashboard/SmartDashboard.h>


#include "Commands/ToggleCommand.h"
#include "Commands/PrepWinch.h"
#include "Commands/ToggleDirection.h"
#include "Commands/WinchCommands.h"
#include "Commands/WinchCommands.h"
#include "Commands/DumpCube.h"
#include "Commands/StowClamp.h"
#include "Commands/StowBucket.h"
#include "Commands/GoToSwitch.h"
#include "Commands/GoToScale.h"
#include "Commands/CurvatureDrive.h"
#include "auto/DriveForward.h"
#include "Commands/ToggleBreaking.h"
#include "OI.h"

#include "Commands/BucketTiltPosition.h"
#include "Commands/ClampPosition.h"
#include "Commands/ClampTiltPosition.h"
#include "Commands/DriveArmsWithJoystick.h"
#include "Commands/DriveWithJoystick.h"
#include "Commands/UpperTiltPosition.h"

#include "Commands/DumpCube.h"
#include "Commands/StowClamp.h"
#include "Commands/StowBucket.h"
#include "Commands/GoToSwitch.h"
#include "Commands/GoToScale.h"
#include "Commands/ResetEncoders.h"

//#include "auto/MotionProfileExecutors.h"
//#include "auto/SwitchDumpSequence.h"
//#include "auto/ScaleDumpSequence.h"
#include "Commands/WinchCommands.h"

OI::OI() {
    llvm::outs() << "OI INIT:END\n";


    Command *clampTiltToSwitch = new ClampTiltToSwitch;
    Command *clampTiltToBucket = new ClampTiltToBucket;
    Command *clampTiltToCube = new ClampTiltToCube;

    controlJoystick.reset(new frc::Joystick(1));
    driveJoystick.reset(new frc::Joystick(0));
    stationButtons.reset(new DriveStation());

    ds_clampToggle.reset(new frc::JoystickButton(stationButtons.get(), 1));
    ds_clampToggle->WhenPressed(
            static_cast<Command *>(new ToggleCommand("clamp toggle", new ClampOpen, new ClampClose)));
    ds_clampToHome.reset(new frc::JoystickButton(stationButtons.get(), 2));
    ds_clampToHome->WhenPressed(clampTiltToBucket);
    ds_clampToCube.reset(new frc::JoystickButton(stationButtons.get(), 3));
    ds_clampToCube->WhenPressed(clampTiltToCube);

    ds_clampToSwitch.reset(new frc::JoystickButton(stationButtons.get(), 4));
    ds_clampToSwitch->WhenPressed(clampTiltToSwitch);

    ds_toScale.reset(new frc::JoystickButton(stationButtons.get(), 5));
    ds_toScale->WhenPressed(new GoToScale);

    ds_toSwitch.reset(new frc::JoystickButton(stationButtons.get(), 6));
    ds_toSwitch->WhenPressed(new GoToSwitch);

    ds_dump.reset(new frc::JoystickButton(stationButtons.get(), 7));
    //ds_dump->WhenPressed(new DumpCube);
    auto autoDump = new BucketTiltAutoDump();
    autoDump->SetInterruptible(false);
    ds_dump->WhileHeld(autoDump);
    ds_dump->WhenReleased(new BucketTiltAllTheWayBack);

    driveArms.reset(new frc::JoystickButton(controlJoystick.get(), 1)); // %rod
    driveArms->WhileHeld(new DriveArmsWithJoystick);
    //TODO: when released, hold position

    toggleClamp.reset(new frc::JoystickButton(controlJoystick.get(), 2));
    toggleClamp->WhenPressed(static_cast<Command *>(new ToggleCommand("clamp toggle", new ClampOpen,
                                                                      new ClampClose)));//(new ClampPosition(-1));// toggle special see clampPosition.cpp
    clamp2Switch.reset(new frc::JoystickButton(controlJoystick.get(), 3));
    clamp2Switch->WhenPressed(clampTiltToSwitch); //(new ClampTiltPosition(215));   // clamp to switch
    clamp2Down.reset(new frc::JoystickButton(controlJoystick.get(), 4));
    clamp2Down->WhenPressed(clampTiltToCube); // clamp down to pickup cube
    clamp2Bucket.reset(new frc::JoystickButton(controlJoystick.get(), 5));
    clamp2Bucket->WhenPressed(clampTiltToBucket); //	clamp to bucket

    goToSwitch.reset(new frc::JoystickButton(controlJoystick.get(), 6));
    goToSwitch->WhenPressed(new GoToSwitch);      // bucket to switch
    goToScale.reset(new frc::JoystickButton(controlJoystick.get(), 7));
    goToScale->WhenPressed(new GoToScale);  // bucket to scale.

    dumpCube.reset(new frc::JoystickButton(controlJoystick.get(), 8));
    dumpCube->WhileHeld(new BucketTiltAutoDump);
    dumpCube->WhenReleased(new BucketTiltAllTheWayBack);
    //dumpCube->WhenPressed(new DumpCube);
    // dump, delay and home bucket
    stowBucket.reset(new frc::JoystickButton(controlJoystick.get(), 9));
    stowBucket->WhenPressed(new StowBucket);  // Stow clamp, then bucket

    winchDisable.reset(new frc::JoystickButton(controlJoystick.get(), 10));
    winchDisable->WhenPressed(new WinchDisable);

    winchUp.reset(new frc::JoystickButton(controlJoystick.get(), 11));
    winchUp->WhileHeld(new WinchUp);
    winchUp->WhenReleased(new WinchHold);


    toggleDirection.reset(new frc::JoystickButton(driveJoystick.get(), 2));
    toggleDirection->WhenPressed(new ToggleDirection);

//	winchStop.reset(new JoystickButton(controlJoystick.get(),9));
//	winchStop->WhileHeld(new WinchDisable);
    //TODO: should the controller joystick have a winch stop also? see above.

    dwinchPrep.reset(new frc::JoystickButton(driveJoystick.get(), 5));
    dwinchPrep->WhenPressed(new PrepWinch);

    dwinchUp.reset(new frc::JoystickButton(driveJoystick.get(), 7));
    dwinchUp->WhileHeld(new WinchUp);
    dwinchUp->WhenReleased(new WinchHold);

    dwinchDown.reset(new frc::JoystickButton(driveJoystick.get(), 9));
    dwinchDown->WhileHeld(new WinchDown);

    dwinchStop.reset(new frc::JoystickButton(driveJoystick.get(), 11));
    dwinchStop->WhenPressed(new WinchDisable);




//// SmartDashboard Buttons
//	frc::SmartDashboard::PutData("Clamp Close", new ClampClose());//,new ClampPosition(0));
//	frc::SmartDashboard::PutData("Clamp Open",new ClampOpen());// new ClampPosition(220));  // 220 also see ClampPosition.cpp
//	frc::SmartDashboard::PutData("Clamp toggle",new ClampToggle());	//new ClampTiltPosition(84));
//    frc::SmartDashboard::PutData("Clamp tilt to Switch", new ClampTiltToSwitch());//new ClampTiltPosition(215));
//    frc::SmartDashboard::PutData("Clamp tilt to cube",new ClampTiltToCube() );//new ClampTiltPosition(357));
//  //  frc::SmartDashboard::PutData("Bucket Zero", );//new BucketTiltPosition(0));
//    frc::SmartDashboard::PutData("Bucket tilt Home", new BucketTiltAllTheWayBack());//new BucketTiltPosition(-15));
//    frc::SmartDashboard::PutData("Bucket tilt auto level", new BucketTiltAutoLevel());//new BucketTiltPosition(100));
//    frc::SmartDashboard::PutData("Bucket to Switch", new BucketTiltToSwitch());//new BucketTiltPosition(80));
//    frc::SmartDashboard::PutData("Bucket to Scale)",new BucketTiltToScale());// new BucketTiltPosition(205));
//    frc::SmartDashboard::PutData("BucketAutoDump", new BucketTiltAutoLevel());//new BucketTiltPosition(200));
//    frc::SmartDashboard::PutData("Dump Cube", new DumpCube());
//    frc::SmartDashboard::PutData("UpperTilt2Home", new UpperTiltToHome());
//    frc::SmartDashboard::PutData("UpperTilt2Switch", new UpperTiltToSwitch());
//    frc::SmartDashboard::PutData("UpperTilt2Scale", new UpperTiltToScale());
//    frc::SmartDashboard::PutData("StowClamp", new StowClamp());
//    frc::SmartDashboard::PutData("GoToSwitch", new GoToSwitch());
//    frc::SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    // frc::SmartDashboard::PutData("Winch Up", new WinchUp());
    // frc::SmartDashboard::PutData("Winch Down", new WinchDown());
//    frc::SmartDashboard::PutData(new CurvatureDrive());
//    frc::SmartDashboard::PutData(new DriveWithJoystick());


    frc::SmartDashboard::PutData(new ResetDriveTrainEncoders());
    //frc::SmartDashboard::PutData(new ResetAllEncoders());
//	frc::SmartDashboard::PutData(new ResetClampEncoder());
//	frc::SmartDashboard::PutData(new ResetClampTiltEncoder());
    //frc::SmartDashboard::PutData(new ResetAllEncoders());



//    frc::SmartDashboard::PutData(new SwitchDumpSequence());
//    frc::SmartDashboard::PutData(new ScaleDumpSequence());
    //  frc::SmartDashboard::PutData(new Straight_10ft());

    llvm::outs() << "OI INIT:END\n";

}


std::shared_ptr<frc::Joystick> OI::getDriveJoystick() {
    return driveJoystick;
}

std::shared_ptr<frc::Joystick> OI::getControlJoystick() {
    return controlJoystick;
}


DriveStation::DriveStation() : frc::GenericHID(2) {}
