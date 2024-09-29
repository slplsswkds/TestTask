#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <boost/asio.hpp>

#include "../../rapidcsv/rapidcsv.h"
#include "../../TcpRxTx/TcpRxTx.h"

boost::asio::ip::tcp::socket connect(const std::string &host, uint16_t port);

class TcpConnection : public TcpRxTx {
public:
    /// Class constructor
    TcpConnection(boost::asio::ip::tcp::socket socket);

    /// receive message from server
    std::string receiveMessage();

    void setCsvDoc(const rapidcsv::Document &doc);

    void saveCsvFile(std::string filename);

    /// Close the connection
    void close();

private:
    rapidcsv::Document docCsv_;
};

#endif //TCPCONNECTION_H
