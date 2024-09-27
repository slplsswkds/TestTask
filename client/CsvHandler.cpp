#include "CsvHandler.h"

#include <ranges>

auto CsvHandler::createCsv() -> std::expected<rapidcsv::Document, std::string> {
    using std::ranges::iota_view;
    using rapidcsv::Document, rapidcsv::LabelParams;

    Document csv_data("", LabelParams(-1, -1));

    try {
        for (const int column: iota_view(0, 6)) {
            for (const int row: iota_view(0, 1024)) {
                auto randData = genRandDataString();
                csv_data.SetCell<std::string>(column, row, randData);
            }
        }
    } catch (std::exception &e) {
        return std::unexpected<std::string>(e.what());
    }
    return csv_data;
}

auto CsvHandler::genRandDataString() -> std::string {
    constexpr uint8_t dataLen = 8;

    const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string random_string;
    random_string.reserve(dataLen);

    for (int i = 0; i < dataLen; ++i) {
        random_string += characters[distribution(generator)];
    }

    return random_string;
}

auto CsvHandler::saveCsv(rapidcsv::Document csvFile, const std::filesystem::path &path) -> std::expected<void, std::exception> {
    try {
        csvFile.Save(path.filename());
    } catch (std::exception &e) {
        return std::unexpected<std::exception>(e);
    }
    return {};
}
