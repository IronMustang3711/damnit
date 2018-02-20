//
// Created by Jason Markham on 2/19/18.
//

#ifndef DAMNIT_SCALEDUMPSEQUENCE_H
#define DAMNIT_SCALEDUMPSEQUENCE_H
#include <Commands/CommandGroup.h>


class ScaleDumpSequence : public frc::CommandGroup {
public:
    ScaleDumpSequence();

protected:
    void End() override;

};


#endif //DAMNIT_SCALEDUMPSEQUENCE_H
