//
// Created by Jason Markham on 2/23/18.
//

#ifndef DAMNIT_READERBOARD_H
#define DAMNIT_READERBOARD_H


#include <string>
#include <utility>
#include <memory>

namespace nt {
    class NetworkTable;
}

struct ReaderBoard {



    static inline void reportClampOpen() { getInstance().postMessage("clamp", "open"); };

    static inline void reportClampClose() { getInstance().postMessage("clamp", "close"); }

    static inline void reportAuto() { getInstance().postMessage("mode", "auto"); };

    static inline void reportAutoName(const std::string &name) {
        getInstance().postMessage("auto", name);
    };

    static inline void reportTeleop() { getInstance().postMessage("mode", "teleop"); };

    static inline void reportInit() { getInstance().postMessage("mode", "init"); };

    static inline void reportDisabled() { getInstance().postMessage("mode", "disabled"); };

    static inline void reportDump() { getInstance().postMessage("bucket", "dump"); };

    static inline void reportBucketToSwitch() { getInstance().postMessage("bucket", "switch"); };

    static inline void reportBucketToScale() { getInstance().postMessage("bucket", "scale"); };

    //void reportWinchUp();
    static inline void reportWinch(const std::string &commandName) {
        getInstance().postMessage("winch", commandName);
    }

    static inline void reportClampTiltToHome() {
        getInstance().postMessage("clampTilt", "home");
    }

    static inline void reportClampTiltToBucket() {
        getInstance().postMessage("clampTilt", "bucket");
    };

    static inline void reportClampTiltToCube() { getInstance().postMessage("clampTilt", "cube"); };

    static inline void reportClampTiltToSwitch() {
        getInstance().postMessage("clampTilt", "switch");
    };


    static inline void reportWinch() {
        getInstance().postMessage("winch","prepare");
    };

    static inline void reportGoToSwitch() {
        getInstance().postMessage("robot","goToSwitch");
    }

    static inline void reportGoToScale() {
        getInstance().postMessage("robot","goToScale");
    }

private:
    ReaderBoard();
    static ReaderBoard &getInstance();
    void postMessage(std::string key, std::string value);

    std::shared_ptr<nt::NetworkTable> tbl;


};


#endif //DAMNIT_READERBOARD_H
