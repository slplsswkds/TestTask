#ifndef CSVRXTX_H
#define CSVRXTX_H

#include "../rapidcsv/rapidcsv.h"
#include "boost/asio.hpp"

class CsvRxTx {
protected:
    boost::asio::ip::tcp::socket socket_;
    rapidcsv::Document docCsv_;

public:
    CsvRxTx(boost::asio::ip::tcp::socket socket, const rapidcsv::Document &docCsv);

    void transmitCsv();
    void receiveCsv();
};


#endif //CSVRXTX_H
