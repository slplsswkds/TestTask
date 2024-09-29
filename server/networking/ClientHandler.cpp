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
