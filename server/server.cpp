#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

#define PORT 4666

int main() {
    try {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), PORT));

        // iterative server
        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::string message = "Hello from iterative server";
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
