#include "CliArgs.h"
#include "expected"
#include "random"
#include <ranges>
#include <print>
#include "../rapidcsv/rapidcsv.h"
#include "CsvHandler.h"

int main(const int argc, const char **argv) {
    CliArgs args;
    args.parse_cli_args(argc, argv);

    const auto csvFileResult = CsvHandler::createCsv(); // create csv

    if (!csvFileResult.has_value()) {
        auto err = csvFileResult.error();
        std::cerr << err << std::endl;
        return 1;
    }

    if (auto res = CsvHandler::saveCsv(csvFileResult.value(), args.getFilename()); !res.has_value()) {
        auto err = res.error();
        std::cerr << std::format("failed to save CSV: {}", err.what()) << std::endl;
    }

    return 0;
}
