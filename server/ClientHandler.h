#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <boost/asio.hpp>
#include "../rapidcsv/rapidcsv.h"

class ClientHandler {
public:
    ClientHandler(boost::asio::ip::tcp::socket socket);
    void handle();

private:
    boost::asio::ip::tcp::socket socket_;

    rapidcsv::Document file_;

    void receiveFile(); // Accept file from server
    void editFile(); // edit received file
    void sendFile(); // send modified file
    void sendChangelist(); // send changelist in json format
};


#endif //CLIENTHANDLER_H
