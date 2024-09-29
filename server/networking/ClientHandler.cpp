#include "ClientHandler.h"

#include <fstream>

ClientHandler::ClientHandler(boost::asio::ip::tcp::socket socket)
    : TcpRxTx(std::move(socket)) {
}

void ClientHandler::handle() {
    const auto json = receiveJson();
    auto wrapper = CsvWrapper::deserializeFromJson(json);
}

void ClientHandler::editFile() {
}

void ClientHandler::sendChangelist() {
}
