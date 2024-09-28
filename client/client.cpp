#include <expected>
#include <boost/asio.hpp>

#include "../rapidcsv/rapidcsv.h"
#include "CliArgs.h"
#include "CsvHandler.h"

int main(const int argc, const char **argv) {

    CliArgs args;
    if (args.parse_cli_args(argc, argv)) {
        return 1; // exit if an error occurred while parsing the CLI arguments ar passed --help message
    }

    const auto csvFileResult = CsvHandler::createCsv(); // create csv

    // rewrite error handling
    if (!csvFileResult.has_value()) {
        auto err = csvFileResult.error();
        std::cerr << std::format("failed to create CSV: {}", err) << std::endl;
        return 1;
    }

    // rewrite error handling
    if (auto res = CsvHandler::saveCsv(csvFileResult.value(), args.getFilename()); !res.has_value()) {
        auto err = res.error();
        std::cerr << std::format("failed to save CSV: {}", err) << std::endl;
    }

    return 0;
}
