#include "ClientHandler.h"

#include <fstream>
#include <ranges>
#include <regex>

Changelist::Changelist(const size_t changes, const size_t deletes) : changes_(changes), deletes_(deletes) {
}

ClientHandler::ClientHandler(boost::asio::ip::tcp::socket socket)
    : TcpRxTx(std::move(socket)) {
}

void ClientHandler::handle() {
    // receive file from client
    auto wrapper = CsvWrapper::deserializeFromJson(receiveJson());
    this->docCsv_ = wrapper.csvDoc_;

    // edit file
    auto changelist = editFile();

    // move edited file and counters value
    wrapper.csvDoc_ = this->docCsv_;
    wrapper.changed_ = changelist.changes_;
    wrapper.deleted_ = changelist.deletes_;

    // transmit edited file to the server
    transmitJson(wrapper.serializeToJson());
}

Changelist ClientHandler::editFile() {
    using std::ranges::iota_view;

    size_t changes = 0;
    size_t deletes = 0;

    const uint rowCount = docCsv_.GetRowCount();
    const uint columnCount = docCsv_.GetColumnCount();

    const std::regex vowelRegex("^[aeiouyAEIOUY]"); // A regular expression to check if a string starts with a vowel

    for (const int row: iota_view(0, static_cast<int>(rowCount))) {
        for (const int col: iota_view(0, static_cast<int>(columnCount))) {
            auto cellVal = docCsv_.GetCell<std::string>(col, row);

            if (std::regex_search(cellVal, vowelRegex)) {
                deletes++;
            } else {
                // Replace odd numbers with #
                std::ranges::transform(cellVal, cellVal.begin(), [&](const char c) {
                    if (std::isdigit(c) && (c - '0') % 2 != 0) {
                        changes++;
                        return '#';
                    }
                    return c;
                });

                // Update docCsv_ cell
                docCsv_.SetCell(col, row, cellVal);
            }
        }
    }

    return Changelist{changes, deletes};
}
