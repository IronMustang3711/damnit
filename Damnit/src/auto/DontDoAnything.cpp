//
// Created by Jason Markham on 2/15/18.
//

#include "DontDoAnything.h"

DontDoAnything::DontDoAnything() {

}

void DontDoAnything::Initialize() {
    Command::Initialize();
}

bool DontDoAnything::IsFinished() {
    return false;
}
