//
// Created by Jason Markham on 2/13/18.
//

#ifndef DAMNIT_DRIVEFORWARD_H
#define DAMNIT_DRIVEFORWARD_H


#include <Commands/Command.h>

class DriveForward : public frc::Command {
public:
    explicit DriveForward(double distanceInches);

    DriveForward();

protected:
    void Initialize() override;

    bool IsFinished() override;

    void End() override;


private:
    double distance;

};


#endif //DAMNIT_DRIVEFORWARD_H
