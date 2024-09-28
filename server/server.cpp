#include <boost/asio.hpp>
#include <iostream>
#include "networking/TcpServer.h"

using boost::asio::ip::tcp;

#define PORT 4666

int main() {
    try {
        TcpServer server(PORT);
        server.run_iterative();
    } catch (const std::exception& e) {
        std::cerr << "Failed to start server: " << e.what() << std::endl;
    }
    return 0;
}
