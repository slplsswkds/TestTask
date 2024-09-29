#include <boost/asio.hpp>
#include <iostream>
#include "networking/TcpServer.h"
#include "logging/logging.h"

using boost::asio::ip::tcp;

#define PORT 4666

int main() {
    try {
        init_logging();
        TcpServer server(PORT);
        server.run_iterative();
    } catch (const std::exception &e) {
        BOOST_LOG_TRIVIAL(fatal) << "Failed to start server: " << e.what() << std::endl;
    }
    return 0;
}
