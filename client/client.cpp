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

    std::cout << args.getFilename() << std::endl; // debug message
    std::cout << args.getTargetIp() << std::endl; // debug message
    std::cout << args.getTargetPort() << std::endl; // debug message

    const auto csvFile = CsvHandler::createCsv();

    if (!csvFile.has_value()) {
        auto err = csvFile.error();
        std::cerr << "failed to create CSV" << std::endl;
        // HANDLE ERROR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
    }

    if (auto res = CsvHandler::saveCsv(csvFile.value(), args.getFilename()); !res.has_value()) {
        auto err = res.error();
        std::cerr << "failed to save CSV" << std::endl;
        // HANDLE ERROR !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
    }

    return 0;
}
