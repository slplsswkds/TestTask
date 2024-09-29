#include <boost/asio.hpp>

#include "../rapidcsv/rapidcsv.h"
#include "cli/CliArgs.h"
#include "csv_utils/CsvGenerator.h"
#include "networking/TcpConnection.h"

int main(const int argc, const char **argv) {
    CliArgs args;
    if (args.parse_cli_args(argc, argv)) {
        return 1; // exit if an error occurred while parsing the CLI arguments ar passed --help message
    }

    rapidcsv::Document csvDoc;
    try {
        csvDoc = CsvGenerator::createCsv();
    } catch (const std::exception &e) {
        auto errorMsg = std::format("An error occurred while creating the CSV file: {}", e.what());
        return 0;
    }

    try {
        csvDoc.Save(args.getFilename());
    } catch (const std::exception &e) {
        auto errorMsg = std::format("Failed to save SVG file: {}", e.what());
    }

    auto socket = connect(args.getTargetIp(), args.getTargetPort());
    if (!socket.is_open()) {
        std::cerr << "Cannot estable connection with server" << std::endl;
        return 1;
    }

    auto client = TcpConnection(std::move(socket));
    client.setCsvDoc(csvDoc);
    client.transmitCsv();
    client.receiveCsv();
    client.close();

    return 0;
}
