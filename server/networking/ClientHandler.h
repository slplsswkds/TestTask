#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <boost/asio.hpp>
#include "../../rapidcsv/rapidcsv.h"
#include "../../CsvRxTx/CsvRxTx.h"


class ClientHandler : public CsvRxTx {
public:
    ClientHandler(boost::asio::ip::tcp::socket socket);

    void handle();

private:
    void editFile(); // edit received file
    void sendChangelist(); // send changelist in json format
};


#endif //CLIENTHANDLER_H
