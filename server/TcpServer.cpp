#include "TcpServer.h"

#include <string>
#include <iostream>

TcpServer::TcpServer(const unsigned short port)
    : acceptor_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
}

void TcpServer::run_iterative() {
    try {
        while (true) {
            // wait for new input connection
            boost::asio::ip::tcp::socket socket(io_context_);
            acceptor_.accept(socket);

            // handle client
            handleClient(std::move(socket));
        }
    } catch (const std::exception &e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }
}

void TcpServer::handleClient(boost::asio::ip::tcp::socket socket) {
    try {
        std::string message = "Hello from iterative TCP server\n";
        boost::system::error_code ignored_error;

        // Надсилаємо повідомлення клієнту
        boost::asio::write(socket, boost::asio::buffer(message), ignored_error);

        std::cout << "Sent message to client" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Client handling error: " << e.what() << std::endl;
    }
}
