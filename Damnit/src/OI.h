// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef OI_H
#define OI_H
#include <memory>
#include <Joystick.h>
#include <Buttons/JoystickButton.h>
#include "Commands.h"


class DriveStation : public frc::GenericHID {
public:
	DriveStation();
	inline double GetX(JoystickHand) const override {return 0.0;};
	double GetY(frc::GenericHID::JoystickHand) const override { return 0.0;} ;

};
class OI {
private:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	
	
	
	std::shared_ptr<frc::Joystick> controlJoystick;
	std::shared_ptr<frc::Joystick> driveJoystick;
	std::shared_ptr<DriveStation> stationButtons;

	std::shared_ptr<frc::JoystickButton> ds_clampToggle;
	std::shared_ptr<frc::JoystickButton> ds_clampToHome;
	std::shared_ptr<frc::JoystickButton> ds_clampToCube;
	std::shared_ptr<frc::JoystickButton> ds_clampToSwitch;
	std::shared_ptr<frc::JoystickButton> ds_toScale;
	std::shared_ptr<frc::JoystickButton> ds_toSwitch;
	std::shared_ptr<frc::JoystickButton> ds_dump;


	std::shared_ptr<frc::JoystickButton> driveArms;
	std::shared_ptr<frc::JoystickButton> toggleClamp;
	std::shared_ptr<frc::JoystickButton> clamp2Down;
	std::shared_ptr<frc::JoystickButton> clamp2Switch;
	std::shared_ptr<frc::JoystickButton> clamp2Bucket;
	std::shared_ptr<frc::JoystickButton> clampClose;

	std::shared_ptr<frc::JoystickButton> goToSwitch;
	std::shared_ptr<frc::JoystickButton> goToScale;
	std::shared_ptr<frc::JoystickButton> dumpCube;
	std::shared_ptr<frc::JoystickButton> stowBucket;

	std::shared_ptr<frc::JoystickButton> winchUp;
	std::shared_ptr<frc::JoystickButton> winchDisable;
	std::shared_ptr<frc::JoystickButton> dwinchPrep;
	std::shared_ptr<frc::JoystickButton> winchStop;
	std::shared_ptr<frc::JoystickButton> dwinchUp;
	std::shared_ptr<frc::JoystickButton> dwinchDown;
	std::shared_ptr<frc::JoystickButton> dwinchStop;

    std::shared_ptr<frc::JoystickButton> toggleDirection;



    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<frc::Joystick> controlJoystick2;

public:
	explicit OI(Commands& commands);

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES

	std::shared_ptr<frc::Joystick> getDriveJoystick();
	std::shared_ptr<frc::Joystick> getControlJoystick();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES
};

#endif
