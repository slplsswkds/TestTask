#include "TcpConnection.h"
#include <iostream>

boost::asio::ip::tcp::socket connect(const std::string &host, const uint16_t port) {
    using namespace boost::asio;
    io_service io_service;
    ip::tcp::socket socket(io_service);
    const auto endpoint = ip::tcp::endpoint(ip::address::from_string(host), port);
    socket.connect(endpoint);

    return socket;
}

TcpConnection::TcpConnection(boost::asio::ip::tcp::socket socket)
    : TcpRxTx(std::move(socket)) {
}

std::string TcpConnection::receiveMessage() {
    try {
        boost::asio::streambuf buffer;
        boost::asio::read_until(socket_, buffer, "\n"); // Assume that the message ends with a character '\n'
        std::istream input_stream(&buffer);
        std::string message;
        std::getline(input_stream, message);
        return message;
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while receiving message: " << e.what() << std::endl;
        return "";
    }
}

void TcpConnection::setCsvDoc(const rapidcsv::Document &doc) {
    docCsv_ = doc;
}

void TcpConnection::saveCsvFile(std::string filename) {
    docCsv_.Save(filename);
}

void TcpConnection::close() {
    try {
        socket_.close();
        std::cout << "Connection closed." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while closing the connection: " << e.what() << std::endl;
    }
}
