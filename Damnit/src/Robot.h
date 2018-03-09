

#pragma once

#include <TimedRobot.h>
#include <Commands/Command.h>
#include <SmartDashboard/SmartDashboard.h>
#include <SmartDashboard/SendableChooser.h>
#include <map>

#include "RobotMap.h"

#include "Subsystems/Bucket.h"
#include "Subsystems/Chassis.h"
#include "Subsystems/Clamp.h"
#include "Subsystems/ClampTilt.h"
#include "Subsystems/UpperTilt.h"



#include "Subsystems/Winch.h"

#include "OI.h"

//TODO: investigate forward-declaring subsystem types for reduced comilation time
class AutoSelector; //#include "auto/AutoSelector.h"

class Robot : public frc::TimedRobot {
public:
    static bool isCompetitionRobot;

    frc::Command *autonomousCommand = nullptr;

    static std::unique_ptr<OI> oi;
    static std::shared_ptr<UpperTilt> upperTilt;
    static std::shared_ptr<Bucket> bucket;
    static std::shared_ptr<ClampTilt> clampTilt;
    static std::shared_ptr<Chassis> chassis;
    static std::shared_ptr<Clamp> clamp;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    static std::shared_ptr<Winch> winch;



    void RobotInit() override;

    void DisabledInit() override;

    void DisabledPeriodic() override;

    void AutonomousInit() override;

    void AutonomousPeriodic() override;

    void TeleopInit() override;

    void TeleopPeriodic() override;

    void TestPeriodic() override;

    void TestInit() override;

    void RobotPeriodic() override;


private:
    void updateAllianceColor();


   // void initAutoChooser();

    //frc::Command* getAutoCommand();

   // std::shared_ptr<nt::NetworkTable> autoTable;


//     std::map<std::string, frc::Command *> autos;
//    std::vector<std::string> keys;

    Commands* commands;

    std::unique_ptr<AutoSelector> autoSelector;

};

