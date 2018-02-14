// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "RobotMap.h"
#include <Spark.h>

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
std::shared_ptr<frc::SpeedController> RobotMap::upperTiltUpperMotor;
std::shared_ptr<frc::Encoder> RobotMap::upperTiltUpperEncoder;
std::shared_ptr<frc::SpeedController> RobotMap::bucketBucketMotor;
std::shared_ptr<frc::Encoder> RobotMap::bucketBucketEncoder;
std::shared_ptr<frc::SpeedController> RobotMap::clampTiltMotor;
std::shared_ptr<frc::Encoder> RobotMap::clampTiltEncoder;
std::shared_ptr<WPI_TalonSRX> RobotMap::chassisLeftFront;
std::shared_ptr<WPI_TalonSRX> RobotMap::chassisLeftRear;
std::shared_ptr<frc::SpeedControllerGroup> RobotMap::chassisLeftSide;
std::shared_ptr<WPI_TalonSRX> RobotMap::chassisRightFront;
std::shared_ptr<WPI_TalonSRX> RobotMap::chassisRightRear1;
std::shared_ptr<frc::SpeedControllerGroup> RobotMap::chassisRightSide;
std::shared_ptr<frc::DifferentialDrive> RobotMap::chassisDifferentialDrive;
std::shared_ptr<frc::SpeedController> RobotMap::clampClampMotor;
std::shared_ptr<frc::Encoder> RobotMap::clampClampEncoder;
std::shared_ptr<frc::PowerDistributionPanel> RobotMap::subsystem1PowerDistributionPanel1;

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
std::shared_ptr<frc::SpeedController> RobotMap::winchMotor;

void RobotMap::init() {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS

	upperTiltUpperMotor.reset(new frc::Spark(1));
	std::static_pointer_cast<frc::Spark>(upperTiltUpperMotor)->SetName(
			"UpperTilt", "UpperMotor");

	upperTiltUpperEncoder.reset(
			new frc::Encoder(0, 1, false, frc::Encoder::k4X));
	upperTiltUpperEncoder->SetName("UpperTilt", "UpperEncoder");
	upperTiltUpperEncoder->SetDistancePerPulse(1.0);
	upperTiltUpperEncoder->SetPIDSourceType(frc::PIDSourceType::kDisplacement);
	bucketBucketMotor.reset(new frc::Spark(0));
	std::static_pointer_cast<frc::Spark>(bucketBucketMotor)->SetName("Bucket",
			"BucketMotor");
	bucketBucketEncoder.reset(new frc::Encoder(2, 3, false, frc::Encoder::k4X));
	bucketBucketEncoder->SetName("Bucket", "BucketEncoder");
	bucketBucketEncoder->SetDistancePerPulse(1.0);
	bucketBucketEncoder->SetPIDSourceType(frc::PIDSourceType::kDisplacement);
	clampTiltMotor.reset(new frc::Spark(3));
	std::static_pointer_cast<frc::Spark>(clampTiltMotor)->SetName("ClampTilt",
			"Motor");
	clampTiltEncoder.reset(new frc::Encoder(4, 5, false, frc::Encoder::k4X));
	clampTiltEncoder->SetName("ClampTilt", "Encoder");
	clampTiltEncoder->SetDistancePerPulse(1.0);
	clampTiltEncoder->SetPIDSourceType(frc::PIDSourceType::kDisplacement);
	chassisLeftFront.reset(new WPI_TalonSRX(1));
	chassisLeftFront->SetName("chassis", "left front");

	chassisLeftRear.reset(new WPI_TalonSRX(2));
	chassisLeftRear->SetName("Chassis", "left rear");

	chassisLeftSide = std::make_shared<frc::SpeedControllerGroup>(
			*chassisLeftFront, *chassisLeftRear);
	chassisLeftSide->SetName("Chassis", "LeftSide");

	chassisRightFront.reset(new WPI_TalonSRX(3));
	chassisRightFront->SetName("Chassis", "right front");

	chassisRightRear1.reset(new WPI_TalonSRX(4));
	chassisRightRear1->SetName("Chassis", "right rear");

	chassisRightSide = std::make_shared<frc::SpeedControllerGroup>(
			*chassisRightFront, *chassisRightRear1);
	chassisRightSide->SetName("Chassis", "RightSide");
	chassisDifferentialDrive.reset(
			new frc::DifferentialDrive(*chassisLeftSide, *chassisRightSide));
	chassisDifferentialDrive->SetName("Chassis", "Differential Drive");
	chassisDifferentialDrive->SetSafetyEnabled(true);
	chassisDifferentialDrive->SetExpiration(0.5);
	chassisDifferentialDrive->SetMaxOutput(1.0);

	clampClampMotor.reset(new frc::Spark(2));
	std::static_pointer_cast<frc::Spark>(clampClampMotor)->SetName("Clamp",
			"ClampMotor");
	clampClampEncoder.reset(new frc::Encoder(6, 7, false, frc::Encoder::k4X));
	clampClampEncoder->SetName("Clamp", "ClampEncoder");
	clampClampEncoder->SetDistancePerPulse(1.0);
	clampClampEncoder->SetPIDSourceType(frc::PIDSourceType::kDisplacement);
	subsystem1PowerDistributionPanel1.reset(new frc::PowerDistributionPanel(10));
	subsystem1PowerDistributionPanel1->SetName("Robot",
			"Power Distribution Panel");

	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	winchMotor.reset(new frc::Spark(4));
	std::static_pointer_cast<frc::Spark>(winchMotor)->SetName("Winch",
			"winchMotor");

}
