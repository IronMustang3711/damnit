
#include <PIDController.h>

#include "Bucket.h"
#include "RobotMap.h"


Bucket::Bucket() : PIDSubsystem("Bucket", 0.025, 0.0, 0.0) {
    SetAbsoluteTolerance(5.0);
    GetPIDController()->SetContinuous(false);

    GetPIDController()->SetName("Bucket PID Controller");

    bucketMotor = RobotMap::bucketBucketMotor;
    bucketEncoder = RobotMap::bucketBucketEncoder;
}

double Bucket::ReturnPIDInput() {
    return bucketEncoder->PIDGet();
}

void Bucket::UsePIDOutput(double output) {
    bucketMotor->PIDWrite(output);
}


void Bucket::reset() {
    bucketMotor->StopMotor();
    bucketEncoder->Reset();
}
