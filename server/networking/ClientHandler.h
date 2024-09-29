#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <boost/asio.hpp>
#include "../../TcpRxTx/TcpRxTx.h"
#include "../../rapidcsv/rapidcsv.h"


class ClientHandler : public TcpRxTx {
public:
    ClientHandler(boost::asio::ip::tcp::socket socket);

    void handle();

private:
    rapidcsv::Document docCsv_;

    void editFile(); // edits the resulting file, saves it in the file field, and returns changelist
    void sendChangelist(); // send changelist in json format
};


#endif //CLIENTHANDLER_H
