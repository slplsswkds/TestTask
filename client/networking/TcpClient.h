#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <boost/asio.hpp>

class TcpClient {
public:
    /// Class constructor
    explicit TcpClient(const std::string &host, uint16_t port);

    /// connect to the server
    bool connect();

    /// send message to server
    bool sendMessage(const std::string &message);

    /// receive message from server
    std::string receiveMessage();

    /// Close the connection
    void close();

private:
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::ip::tcp::endpoint endpoint_;
};

#endif //TCPCLIENT_H
