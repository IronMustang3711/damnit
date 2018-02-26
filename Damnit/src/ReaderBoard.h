//
// Created by Jason Markham on 2/23/18.
//

#ifndef DAMNIT_READERBOARD_H
#define DAMNIT_READERBOARD_H


#include <string>
#include <utility>
namespace nt{
    class NetworkTable;
}

struct ReaderBoard {

    static ReaderBoard& getInstance();

    void reportClampOpen();
    void reportClampClose();
    void reportAuto();
    void reportAutoName(const std::string& name);
    void reportTeleop();
    void reportInit();
    void reportDisabled();
    void reportDump();
    void reportBucketToSwitch();
    void reportBucketToScale();
    void reportWinchUp();
    void reportClampTiltToHome();
    void reportClampTiltToCube();
    void reportClampTiltToSwitch();



private:
    ReaderBoard();
    void postMessage(std::string key, std::string value);
    std::shared_ptr<nt::NetworkTable> tbl;


};


#endif //DAMNIT_READERBOARD_H
