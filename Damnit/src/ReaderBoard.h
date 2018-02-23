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

    void postMessage(std::string key, std::string value);

private:
    ReaderBoard();
    std::shared_ptr<nt::NetworkTable> tbl;


};


#endif //DAMNIT_READERBOARD_H
