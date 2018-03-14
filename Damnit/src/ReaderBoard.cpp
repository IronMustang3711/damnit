//
// Created by Jason Markham on 2/23/18.
//

#include <networktables/NetworkTableInstance.h>
#include "ReaderBoard.h"

ReaderBoard::ReaderBoard() {
    tbl = nt::NetworkTableInstance::GetDefault().GetTable("matrixPanel");
}

void ReaderBoard::postMessage(std::string key, std::string value) {
    tbl->PutString(key, value);
}

ReaderBoard &ReaderBoard::getInstance() {
    static ReaderBoard instance;
    return instance;
}

//void ReaderBoard::reportWinch() {
//    getInstance().postMessage("winch","prepare");
//
//}
//
//void ReaderBoard::reportGoToSwitch() {
//    getInstance().postMessage("robot","goToSwitch");
//}
//
//void ReaderBoard::reportGoToScale() {
//    getInstance().postMessage("robot","goToScale");
//}

//void ReaderBoard::reportClampOpen() {
//    postMessage("clamp", "open");
//}
//
//void ReaderBoard::reportClampClose() {
//    postMessage("clamp", "close");
//}
//
//void ReaderBoard::reportTeleop() {
//    postMessage("mode", "teleop");
//}
//
//void ReaderBoard::reportAuto() {
//    postMessage("mode", "auto");
//}
//
//void ReaderBoard::reportInit() {
//    postMessage("mode", "init"); //TODO: ("initialized", "true") ?
//}
//
//void ReaderBoard::reportDisabled() {
//    postMessage("mode", "disabled");
//}
//
//void ReaderBoard::reportAutoName(const std::string &name) {
//    postMessage("auto", name);
//}
//
//void ReaderBoard::reportDump() {
//    postMessage("bucket", "dump");
//}
//
//void ReaderBoard::reportBucketToSwitch() {
//    postMessage("bucket", "switch");
//}
//
//void ReaderBoard::reportBucketToScale() {
//    postMessage("bucket", "scale");
//}
//
//void ReaderBoard::reportClampTiltToHome() {
//    postMessage("clampTilt", "home");
//}
//void ReaderBoard::reportClampTiltToBucket() {
//    postMessage("clampTilt", "bucket");
//}
//
//void ReaderBoard::reportClampTiltToCube() {
//    postMessage("clampTilt", "cube");
//}
//
//void ReaderBoard::reportClampTiltToSwitch() {
//    postMessage("clampTilt", "switch");
//}
//
//void ReaderBoard::reportWinch(const std::string commandName) {
//postMessage("winch",commandName);
//}