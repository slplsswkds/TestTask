#include "CliArgs.h"
#include "expected"
#include "random"
#include <ranges>
#include <print>
#include "../rapidcsv/rapidcsv.h"

auto createCsv() -> std::expected<rapidcsv::Document, std::string>; /// creates CSV file and fills them with random data
auto genRandDataString() -> std::string; /// create string of random numbers and latin letters
auto saveCsv(rapidcsv::Document csvFile, const std::filesystem::path &path) -> std::expected<void, std::exception>;

int main(const int argc, const char **argv) {
    CliArgs args;
    args.parse_cli_args(argc, argv);

    std::cout << args.getFilename() << std::endl; // debug message
    std::cout << args.getTargetIp() << std::endl; // debug message
    std::cout << args.getTargetPort() << std::endl; // debug message

    const auto csvFile = createCsv();

    if (!csvFile.has_value()) {
        auto err = csvFile.error();
        std::cerr << "failed to create CSV" << std::endl;
        // HANDLE ERROR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
    }

    if (auto res = saveCsv(csvFile.value(), args.getFilename()); !res.has_value()) {
        auto err = res.error();
        std::cerr << "failed to save CSV" << std::endl;
        // HANDLE ERROR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
    }

    return 0;
}

// Creates and fills CSV file
auto createCsv() -> std::expected<rapidcsv::Document, std::string> {
    using std::ranges::iota_view;
    using rapidcsv::Document, rapidcsv::LabelParams;

    Document csv_data("", LabelParams(-1, -1));

    try {
        for (const int column: iota_view(0, 6)) {
            for (const int row: iota_view(0, 1024)) {
                // std::cout << "setting!" << std::endl;
                std::println("({},{})", column, row);
                auto randData = genRandDataString();
                csv_data.SetCell<std::string>(column, row, randData);
            }
        }
    } catch (std::exception &e) {
    }
    return csv_data;
}

/// REWRITE THIS!!!!! I should delete characters array and use number ranges  !!!!
auto genRandDataString() -> std::string {
    // ASCII codes for numbers:         0d48 - 0d57
    // ASCII codes for latin letters:   0d65 - 0d90    (high register)
    // ASCII codes for latin letters:   0d97 - 0d122    (low register)
    constexpr uint8_t dataLen = 8;

    const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string random_string;
    random_string.reserve(dataLen);

    for (int character: std::ranges::iota_view(0, 9)) {
        random_string += characters[distribution(generator)];
    }

    return random_string;
}

auto saveCsv(rapidcsv::Document csvFile, const std::filesystem::path &path) -> std::expected<void, std::exception> {
    try {
        csvFile.Save(path.filename());
    } catch (std::exception &e) {
    }
    return {};
}
