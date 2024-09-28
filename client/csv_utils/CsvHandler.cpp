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
    } catch (const std::exception &e) {
        auto errorMsg = std::format("An error occurred while creating the CSV file: {}", e.what());
        return std::unexpected<std::string>(errorMsg);
    } catch (...) {
        // for unknown errors
        return std::unexpected<std::string>("Unknown error occurred while creating CSV.");
    }

    return csv_data;
}


auto CsvHandler::genRandDataString() -> std::string {
    constexpr uint8_t dataLen = 8;

    std::random_device rd;
    std::mt19937 generator(rd());

    // [48-57] numbers range in th ASCII table
    // [97-122] latin letters in th ASCII table
    std::uniform_int_distribution<> distribution(0, 34); // 10 numbers + 25 letters = 35 chars

    std::string random_string;
    random_string.reserve(dataLen);

    for (int i = 0; i < dataLen; ++i) {
        if (const int rand_index = distribution(generator); rand_index <= 9) {
            random_string += static_cast<char>(48 + rand_index); // 48-57: цифри
        } else {
            random_string += static_cast<char>(87 + rand_index); // 97-122: літери (97 = 87 + 10)
        }
    }

    return random_string;
}

auto CsvHandler::saveCsv(rapidcsv::Document csvFile,
                         const std::filesystem::path &path) -> std::expected<void, std::string> {
    try {
        csvFile.Save(path.filename());
    } catch (std::exception &e) {
        return std::unexpected(e.what());
    }
    return {};
}
