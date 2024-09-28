#include <expected>
#include <boost/asio.hpp>

#include "../rapidcsv/rapidcsv.h"
#include "cli/CliArgs.h"
#include "csv_utils/CsvHandler.h"
#include "networking/TcpClient.h"

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

    // endpoint to the server
    auto endpoint = boost::asio::ip::tcp::endpoint(
        boost::asio::ip::address::from_string(args.getTargetIp()),
        args.getTargetPort()
    );

    auto client = std::make_unique<TcpClient>(endpoint);
    if (!client->connect()) {
        std::cerr << "failed to connect to the server" << std::endl;
    }

    const std::string response = client->receiveMessage();
    std::cout << "Received: " << response << std::endl;

    client->close(); // close the connection

    return 0;
}
