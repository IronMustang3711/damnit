//
// Created by Jason Markham on 2/23/18.
//

#include <networktables/NetworkTableInstance.h>
#include "ReaderBoard.h"

ReaderBoard::ReaderBoard() {
   tbl = nt::NetworkTableInstance::GetDefault().GetTable("matrixPanel");
}

void ReaderBoard::postMessage(std::string key, std::string value) {
    tbl->PutString(key,value);
}

ReaderBoard &ReaderBoard::getInstance() {
    static ReaderBoard instance;
    return instance;
}

void ReaderBoard::reportClampOpen() {
    postMessage("clamp","open");
}

void ReaderBoard::reportClampClose() {
    postMessage("clamp","close");
}

void ReaderBoard::reportTeleop() {
    postMessage("mode","teleop");
}

void ReaderBoard::reportAuto() {
    postMessage("mode","auto");
}

void ReaderBoard::reportInit() {
    postMessage("mode","init"); //TODO: ("initialized", "true") ?
}

void ReaderBoard::reportDisabled() {
    postMessage("mode","disabled");
}
