#include "TcpServer.h"

#include <iostream>
#include "ClientHandler.h"
#include "../logging/logging.h"

TcpServer::TcpServer(uint16_t port)
    : acceptor_(io_context_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
}

void TcpServer::run_iterative() {
    BOOST_LOG_TRIVIAL(debug) << "Starting iterative server..." << std::endl;

    while (true) {
        // wait for new input connection
        boost::asio::ip::tcp::socket socket(io_context_);
        acceptor_.accept(socket);

        BOOST_LOG_TRIVIAL(info) << "New input connection: " << socket.remote_endpoint().address().to_string() << std::endl;

        // handle client
        try {
            auto handler = ClientHandler(std::move(socket));
            handler.handle();
            socket.close();
            BOOST_LOG_TRIVIAL(info) << "Connection closed successfully";
        } catch (const std::exception &e) {
            BOOST_LOG_TRIVIAL(error) << "Failed to handle client: " << e.what() << std::endl;
        }
    }
}
