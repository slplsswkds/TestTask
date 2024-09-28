#include "TcpClient.h"
#include <iostream>

TcpClient::TcpClient(const std::string &host, const uint16_t port)
    : socket_(io_context_), endpoint_(boost::asio::ip::address::from_string(host), port) {
}

bool TcpClient::connect() {
    try {
        socket_.connect(endpoint_);
        std::cout << "Successfully connected to the server." << std::endl;
        return true;
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while connecting to the server: " << e.what() << std::endl;
        return false;
    }
}

bool TcpClient::sendMessage(const std::string &message) {
    try {
        boost::asio::write(socket_, boost::asio::buffer(message));
        return true;
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while sending message: " << e.what() << std::endl;
        return false;
    }
}

std::string TcpClient::receiveMessage() {
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

void TcpClient::close() {
    try {
        socket_.close();
        std::cout << "Connection closed." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "An error occurred while closing the connection: " << e.what() << std::endl;
    }
}
