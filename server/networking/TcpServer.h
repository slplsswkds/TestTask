#ifndef TCPSERVER_H
#define TCPSERVER_H


#include <boost/asio.hpp>

class TcpServer {
public:
    explicit TcpServer(unsigned short port);

    void run_iterative(); // run iterative server

private:
    boost::asio::io_context io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
};


#endif //TCPSERVER_H
