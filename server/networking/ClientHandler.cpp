#include "ClientHandler.h"

#include <fstream>

ClientHandler::ClientHandler(boost::asio::ip::tcp::socket socket)
    : CsvRxTx(std::move(socket)) {
}

void ClientHandler::handle() {
    receiveCsv();
    editFile();
    transmitCsv();
    sendChangelist();
}

void ClientHandler::editFile() {
}

void ClientHandler::sendChangelist() {
}
