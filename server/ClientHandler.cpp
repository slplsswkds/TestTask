#include "ClientHandler.h"

#include <iostream>
#include <ranges>
#include <random>

ClientHandler::ClientHandler(boost::asio::ip::tcp::socket socket) : socket_(std::move(socket)) {
}

void ClientHandler::handle() {
    receiveFile();
    editFile();
    sendFile();
    sendChangelist();
}

void ClientHandler::receiveFile() {
}

void ClientHandler::editFile() {
}

void ClientHandler::sendFile() {
}

void ClientHandler::sendChangelist() {
}
