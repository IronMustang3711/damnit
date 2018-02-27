constexpr double encoder_ticks_per_inch = 76.0;//130;//encoder_ticks_per_rev / distance_per_rev; //74.802823

//TODO: change for proto_bot
constexpr double max_encoder_rate = 1300.0;//max_encoder_rate_per_sec / 10.0;

constexpr double FGain = 1023.0 / (max_encoder_rate - 0.1 * max_encoder_rate);

constexpr inline double inches_to_encoder_ticks(double inches) {
    return inches * encoder_ticks_per_inch;
}

#include <cmath>
#include <llvm/raw_ostream.h>
#include <Robot.h>
#include "Chassis.h"
#include "RobotMap.h"
#include "Commands/DriveWithJoystick.h"


constexpr int SLOT = 0;
constexpr int TIMEOUT = 10;

Chassis::Chassis(double correction) : frc::Subsystem("Chassis"), rotation_correction(correction) {
    leftFront = RobotMap::chassisLeftFront;
    leftRear = RobotMap::chassisLeftRear;
    leftSide = RobotMap::chassisLeftSide;
    rightFront = RobotMap::chassisRightFront;
    rightRear1 = RobotMap::chassisRightRear1;
    rightSide = RobotMap::chassisRightSide;
    differentialDrive = RobotMap::chassisDifferentialDrive;

}

void Chassis::InitDefaultCommand() {
    SetDefaultCommand(new DriveWithJoystick());
}

void Chassis::Periodic() {

//SmartDashboard::PutNumberArray("encoder positions",llvm::ArrayRef<double>({
//	static_cast<double>(leftFront->GetSelectedSensorPosition(0)),
//	static_cast<double>(rightFront->GetSelectedSensorPosition(0))
//}));

    SmartDashboard::PutNumber("encoder position(left)", (double) leftFront->GetSelectedSensorPosition(0));
    SmartDashboard::PutNumber("encoder position(right)", (double) rightFront->GetSelectedSensorPosition(0));

//    SmartDashboard::PutNumberArray("encoder velocity",
//       		llvm::ArrayRef<double>{(double)leftFront->GetSensorCollection().GetQuadratureVelocity(),
//   									(double)rightFront->GetSensorCollection().GetQuadratureVelocity()});

    auto vl = (double) leftFront->GetSelectedSensorVelocity(0);
    auto vr = (double) rightFront->GetSelectedSensorVelocity(0);
    SmartDashboard::PutNumber("encoder velocity(left)", vl);
    SmartDashboard::PutNumber("encoder velocity(right)", vr);

    SmartDashboard::PutNumber("encoder acc(left)", vl - VlPrev);
    SmartDashboard::PutNumber("encoder acc(right)", vr - VrPrev);

    VrPrev = vr;
    VlPrev = vl;

    SmartDashboard::PutString("chassis command",
                              GetCurrentCommand() == nullptr ? "null" : GetCurrentCommand()->GetName());

//   llvm::SmallVector<double,4> outputs;
//    for (const auto t : {leftFront.get(), leftRear.get(), rightFront.get(), rightRear1.get()}) {
//    	outputs.push_back(t->GetMotorOutputPercent());
//    	SmartDashboard::PutNumber("output "+ t->GetName(), t->GetMotorOutputPercent());
//    }
    // SmartDashboard::PutNumberArray("MotorOutputs", outputs);

    if (leftFront->GetControlMode() == ControlMode::MotionMagic
       || leftFront->GetControlMode() == ControlMode ::MotionProfile) {
        for (const auto t : {leftFront.get(), rightFront.get()}) {
            SmartDashboard::PutNumber("closed loop error: " + t->GetName(), t->GetClosedLoopError(SLOT));
            SmartDashboard::PutNumber("closed loop target: " + t->GetName(), t->GetClosedLoopTarget(SLOT));

        }
    }


}


// add tank drive  %rod1
void Chassis::TeleopDrive(std::shared_ptr<Joystick> stickPosition) {
    double y = -stickPosition->GetY();
    double z = stickPosition->GetZ();

    if (reversed) {
      //  z = 1.0 * z;
        y = -1.0 * y;
    }

    // y and z cubed, results in less drive around zero input
    y = pow(y, 3);
    z = pow(z, 3);
    z = z * 0.6;
    z += rotation_correction * y;
    differentialDrive->ArcadeDrive(y, z, false);
}

void Chassis::mm_driveForward_init() {
    prepareForAutonomous();
    for (const auto t : {leftFront.get(), leftRear.get(), rightFront.get(), rightRear1.get()}) {
        t->Config_kP(SLOT, 10.0, TIMEOUT); //TODO: this probably needs to be changed for the proto bot
        t->Config_kI(SLOT, 0.0, TIMEOUT);
        t->Config_kD(SLOT, 0.0, TIMEOUT);
        t->Config_kF(SLOT, FGain, TIMEOUT);

        constexpr double cruise_velocity = 0.5 * max_encoder_rate;
        constexpr double max_accel =0.5 * cruise_velocity;

        t->ConfigMotionCruiseVelocity(static_cast<int>(cruise_velocity), TIMEOUT);
        t->ConfigMotionAcceleration(static_cast<int>(max_accel), TIMEOUT);

    }


    leftRear->Follow(*leftFront);

    rightRear1->Follow(*rightFront);
}

void Chassis::mm_Periodic(double distanceInches) {
    leftRear->Set(ControlMode::Follower, leftFront->GetDeviceID());
    rightRear1->Set(ControlMode::Follower, rightFront->GetDeviceID());

    for (const auto t : {leftFront.get(), rightFront.get()}) {
        t->Set(ControlMode::MotionMagic, inches_to_encoder_ticks(distanceInches));
    }


}

void Chassis::resetEncoders() {
    for (const auto t : {leftFront.get(), rightFront.get()}) {
        //  t->GetSensorCollection().SetQuadraturePosition(0, TIMEOUT);
        t->SetSelectedSensorPosition(0, SLOT, TIMEOUT);
    }
}

void Chassis::prepareForAutonomous() {
    stop();
    for (const auto t : {leftFront.get(), leftRear.get(), rightFront.get(), rightRear1.get()}) {
        t->ConfigVoltageCompSaturation(11.0, TIMEOUT);
        t->EnableVoltageCompensation(true);
    }
    //resetEncoders();

    // disableMotorSafety();
}

void Chassis::prepareForTeleop() {

    for (const auto t : {leftFront.get(), leftRear.get(), rightFront.get(), rightRear1.get()}) {
        t->EnableVoltageCompensation(false);
        //t->SetNeutralMode(NeutralMode::Coast); // reduce the chances of tipping ( hopefully).
    }
    //enableMotorSafety();
}

bool Chassis::driveStraightIsOnTarget() {
    double leftErr = leftFront->GetClosedLoopError(SLOT);
    double rightErr = rightFront->GetClosedLoopError(SLOT);
    llvm::outs() << "err: left=" << leftErr << " right=" << rightErr << " \n";
    return std::abs(leftErr) < 6.0 && std::abs(rightErr) < 6.0;

}

void Chassis::stop() {
    enableInductiveBreaking(true);
    differentialDrive->StopMotor();
}

void Chassis::enableInductiveBreaking(bool enable) {
    for (const auto t : {leftFront.get(), leftRear.get(), rightFront.get(), rightRear1.get()}) {

        t->SetNeutralMode(enable ? NeutralMode::Brake : NeutralMode::Coast);
    }


}

void Chassis::ArcadeDrive(double fwd, double rotate) {
    differentialDrive->ArcadeDrive(fwd, rotate, false);
}

void Chassis::curvatureDrive(double fwd, double rotate, bool quickTurn) {
    differentialDrive->CurvatureDrive(fwd, rotate, quickTurn);
}

void Chassis::disableMotorSafety() {
    for (const auto t : {leftFront.get(), leftRear.get(), rightFront.get(), rightRear1.get()}) {
        t->SetSafetyEnabled(false);
    }
    differentialDrive->SetSafetyEnabled(false);
}

void Chassis::enableMotorSafety() {
    for (const auto t : {leftFront.get(), leftRear.get(), rightFront.get(), rightRear1.get()}) {
        t->SetSafetyEnabled(true);
    }
    differentialDrive->SetSafetyEnabled(true);

}


void Chassis::testPeriodic() {
//	llvm::outs() << "left encoder: " << leftFront->GetSelectedSensorPosition(0)
//			<< " right encoder: "<<rightFront->GetSelectedSensorPosition(0) << "\n";
//	llvm::outs() << "lf " << leftFront->GetMotorOutputPercent()
//			<< "lr "<<leftRear->GetMotorOutputPercent()
//			<<"rf "<<rightFront->GetMotorOutputPercent()
//			<<"rr "<<rightRear1->GetMotorOutputPercent() <<"\n";
}

void Chassis::toggleDirection() {
    reversed = !reversed;
    SmartDashboard::PutBoolean("drive reversed?",reversed);
}

Chassis::Chassis() : Chassis(chassis_config::getConfig().rotation_correction) {

}


const chassis_config::Config &chassis_config::getConfig() {
    return Robot::isCompetitionRobot ? chassis_config::COMPETITION_CONFIG : chassis_config::PROTO_CONFIG;
}
