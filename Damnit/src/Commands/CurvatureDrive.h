//
// Created by Jason Markham on 2/13/18.
//

#ifndef DAMNIT_CURVATUREDRIVE_H
#define DAMNIT_CURVATUREDRIVE_H


#include <Commands/Command.h>

class CurvatureDrive : public frc::Command {
public:
    CurvatureDrive();

protected:
    void Initialize() override;

    void Execute() override;

    bool IsFinished() override;

};


#endif //DAMNIT_CURVATUREDRIVE_H
