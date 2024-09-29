#include "TcpServer.h"

#include <iostream>
#include "ClientHandler.h"

TcpServer::TcpServer(uint16_t port)
    : acceptor_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
}

void TcpServer::run_iterative() {
    try {
        while (true) {
            // wait for new input connection
            boost::asio::ip::tcp::socket socket(io_context_);
            acceptor_.accept(socket);

            // handle client
            auto handler = ClientHandler(std::move(socket));
            handler.handle();
        }
    } catch (const std::exception &e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }
}
