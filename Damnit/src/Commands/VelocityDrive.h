//
// Created by Jason Markham on 3/27/18.
//

#ifndef DAMNIT_VELOCITYDRIVE_H
#define DAMNIT_VELOCITYDRIVE_H

#include "../../../../../wpilib/cpp/current/include/WPILib.h"
#include "../../../../../wpilib/user/cpp/include/ctre/Phoenix.h"
#include "../Robot.h"
#include "../RobotMap.h"

class VelocityDrive : public frc::Command{

 static   constexpr int PRIMARY_PID = 0;
    static   constexpr int TURN_PID = 1;

    static  constexpr int TURN_SLOT = 1;
    static  constexpr int FWD_SLOT = 2;

    static  constexpr int TIMEOUT = 10;
    static  constexpr int REMOTE_0 = 0;

    static constexpr double TravelUnitsPerRotation = 3600;
    static constexpr int EncoderUnitsPerRotation = 6000;
    static constexpr int SensorUnitsPerRotation = 1414;


    void Initialize() override {
        IMotorController& lRef = *left;
        IMotorController& rRef = *right;

        RobotMap::chassisLeftRear->Follow(lRef);
        RobotMap::chassisRightRear1->Follow(rRef);



        left->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder,
                                                PRIMARY_PID,
                                                TIMEOUT);

        /* Remote 0 will be the other side's Talon */
       right->ConfigRemoteFeedbackFilter(	left->GetDeviceID(),
                                                  RemoteSensorSource::RemoteSensorSource_TalonSRX_SelectedSensor,
                                                  REMOTE_0,
                                                 TIMEOUT);

        /* setup sum and difference signals */
        right->ConfigSensorTerm(SensorTerm::SensorTerm_Sum0, FeedbackDevice::RemoteSensor0, TIMEOUT);
        right->ConfigSensorTerm(SensorTerm::SensorTerm_Sum1, FeedbackDevice::QuadEncoder, TIMEOUT);
        right->ConfigSensorTerm(SensorTerm::SensorTerm_Diff1, FeedbackDevice::RemoteSensor0, TIMEOUT);
        right->ConfigSensorTerm(SensorTerm::SensorTerm_Diff0, FeedbackDevice::QuadEncoder, TIMEOUT);
        /* select sum for distance(0), different for turn(1) */
        right->ConfigSelectedFeedbackSensor(FeedbackDevice::SensorSum,PRIMARY_PID, TIMEOUT);



        right->ConfigSelectedFeedbackSensor(FeedbackDevice::SensorDifference,
                                                TURN_PID,
                                                TIMEOUT);

        /* do not scale down the primary sensor (distance) */
        right->ConfigSelectedFeedbackCoefficient(1, PRIMARY_PID,TIMEOUT);

        /* scale empirically measured units to 3600units, this gives us
         * - 0.1 deg resolution
         * - scales to human-readable units
         * - keeps target away from overflow (12bit)
         *
         * Heading units should be scaled to ~4000 per 360 deg, due to the following limitations...
         * - Target param for aux PID1 is 18bits with a range of [-131072,+131072] units.
         * - Target for aux PID1 in motion profile is 14bits with a range of [-8192,+8192] units.
         *  ... so at 3600 units per 360', that ensures 0.1 deg precision in firmware closed-loop
         *  and motion profile trajectory points can range �2 rotations.
         */
        right->ConfigSelectedFeedbackCoefficient(TravelUnitsPerRotation / EncoderUnitsPerRotation, TURN_PID, TIMEOUT);


        /* max out the peak output (for all modes).  However you can
         * limit the output of a given PID object with ConfigClosedLoopPeakOutput().
         */
        left->ConfigPeakOutputForward(+1.0, TIMEOUT);
        left->ConfigPeakOutputReverse(-1.0, TIMEOUT);
        right->ConfigPeakOutputForward(+1.0, TIMEOUT);
        right->ConfigPeakOutputReverse(-1.0, TIMEOUT);

   
        /* turn servo */
        right->Config_kP(TURN_SLOT, 2.0, TIMEOUT);
        right->Config_kI(TURN_SLOT, 0.0, TIMEOUT);
        right->Config_kD(TURN_SLOT, 4.0, TIMEOUT);
        right->Config_kF(TURN_SLOT, 0, TIMEOUT);
      //  right->Config_IntegralZone(TURN_SLOT, Constants.kGains_Turning.kIzone, TIMEOUT);
        right->ConfigClosedLoopPeakOutput(	TURN_SLOT,
                                                  1.0,
                                                  TIMEOUT);

//        /* magic servo */
//        _talonRght.Config_kP(Constants.kSlot_MotProf, Constants.kGains_MotProf.kP, TIMEOUT);
//        _talonRght.Config_kI(Constants.kSlot_MotProf, Constants.kGains_MotProf.kI, TIMEOUT);
//        _talonRght.Config_kD(Constants.kSlot_MotProf, Constants.kGains_MotProf.kD, TIMEOUT);
//        _talonRght.Config_kF(Constants.kSlot_MotProf, Constants.kGains_MotProf.kF, TIMEOUT);
//        _talonRght.Config_IntegralZone(Constants.kSlot_MotProf, Constants.kGains_MotProf.kIzone, TIMEOUT);
//        _talonRght.ConfigClosedLoopPeakOutput(	Constants.kSlot_MotProf,
//                                                  Constants.kGains_MotProf.kPeakOutput,
//                                                  TIMEOUT);


        /* velocity servo */
        right->Config_kP(FWD_SLOT, 0.1, TIMEOUT);
        right->Config_kI(FWD_SLOT, 0, TIMEOUT);
        right->Config_kD(FWD_SLOT, 20, TIMEOUT);
        right->Config_kF(FWD_SLOT, 1023.0/1000.0, TIMEOUT);

        right->ConfigClosedLoopPeakOutput(	FWD_SLOT,
                                                 0.5,
                                                  TIMEOUT);

        left->SetNeutralMode(NeutralMode::Brake);
        right->SetNeutralMode(NeutralMode::Brake);

        /* 1ms per loop.  PID loop can be slowed down if need be.
         * For example,
         * - if sensor updates are too slow
         * - sensor deltas are very small per update, so derivative error never gets large enough to be useful.
         * - sensor movement is very slow causing the derivative error to be near zero.
         */
        int closedLoopTimeMs = 1;
        right->ConfigSetParameter(ParamEnum::ePIDLoopPeriod, closedLoopTimeMs, 0x00, TURN_PID, TIMEOUT);
        right->ConfigSetParameter(ParamEnum::ePIDLoopPeriod, closedLoopTimeMs, 0x00, TURN_PID, TIMEOUT);

        /**
         * false means talon's local output is PID0 + PID1, and other side Talon is PID0 - PID1
         * true means talon's local output is PID0 - PID1, and other side Talon is PID0 + PID1
         */
        right->ConfigAuxPIDPolarity(false, TIMEOUT);

        left->GetSensorCollection().SetQuadraturePosition(0, TIMEOUT);
        right->GetSensorCollection().SetQuadraturePosition(0, TIMEOUT);



        right->SelectProfileSlot(FWD_SLOT, PRIMARY_PID);
        right->SelectProfileSlot(TURN_SLOT, TURN_PID);

    }

    bool IsFinished() override {
        return false;
    }


    void Execute() override {

      double fwd =  -1.0*Robot::oi->getDriveJoystick()->GetY();
      double turn =  -1.0*Robot::oi->getDriveJoystick()->GetTwist();

      double target_rpm = 500.0 * fwd;
      double targetUnitsPer100MS = target_rpm * SensorUnitsPerRotation / 600.0;

      double heading_units = TravelUnitsPerRotation * turn;


        static_cast<BaseMotorController*>(right)->Set(ControlMode::Velocity, targetUnitsPer100MS, DemandType_AuxPID, heading_units);

        left->Follow(*right, FollowerType::FollowerType_AuxOutput1);


    }
    WPI_TalonSRX* left;
    WPI_TalonSRX* right;

public:
    VelocityDrive() : Command("Velocity Drive"){
        Requires(Robot::chassis.get());

        left = RobotMap::chassisRightFront.get();
        right = RobotMap::chassisLeftFront.get();
    }
};


#endif //DAMNIT_VELOCITYDRIVE_H
