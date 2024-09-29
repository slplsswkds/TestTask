#include "ClientHandler.h"

#include <fstream>

ClientHandler::ClientHandler(boost::asio::ip::tcp::socket socket)
    : TcpRxTx(std::move(socket)) {
}

void ClientHandler::handle() {
    auto json = receiveJson();
    // receiveCsv();
    // editFile();
    // transmitCsv();
    // sendChangelist();
}

void ClientHandler::editFile() {
}

void ClientHandler::sendChangelist() {
}
