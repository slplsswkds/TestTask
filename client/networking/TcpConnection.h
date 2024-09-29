#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <boost/asio.hpp>

#include "../../rapidcsv/rapidcsv.h"
#include "../../CsvRxTx/CsvRxTx.h"

boost::asio::ip::tcp::socket connect(const std::string &host, uint16_t port);

class TcpConnection : public CsvRxTx {
public:
    /// Class constructor
    TcpConnection(boost::asio::ip::tcp::socket socket);

    /// receive message from server
    std::string receiveMessage();

    void setCsvDoc(const rapidcsv::Document &doc);

    /// Close the connection
    void close();
};

#endif //TCPCONNECTION_H
