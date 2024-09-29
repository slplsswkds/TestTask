#include "ClientHandler.h"

#include <fstream>

Changelist::Changelist(const size_t changes, const size_t deletes) : changes_(changes), deletes_(deletes) {
}

ClientHandler::ClientHandler(boost::asio::ip::tcp::socket socket)
    : TcpRxTx(std::move(socket)) {
}

void ClientHandler::handle() {
    const auto json = receiveJson();
    auto wrapper = CsvWrapper::deserializeFromJson(json);
    this->docCsv_ = wrapper.csvDoc_;

    auto changelist = editFile();

    wrapper.csvDoc_ = this->docCsv_; // edited file

    auto jsonData = wrapper.serializeToJson();
    jsonData["changes"] = changelist.changes_;
    jsonData["deletes"] = changelist.deletes_;

    transmitJson(jsonData);
}

Changelist ClientHandler::editFile() {
    auto tmp  = docCsv_;
    docCsv_ = tmp;
    return Changelist(0, 0);
}

void ClientHandler::sendChangelist() {
}
