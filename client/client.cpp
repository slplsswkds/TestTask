#include <boost/asio.hpp>

#include "../rapidcsv/rapidcsv.h"
#include "../server/networking/ClientHandler.h"
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

    auto csvWrapper = CsvWrapper(args.getFilename(), csvDoc);
    client.transmitJson(csvWrapper.serializeToJson());

    auto responseJson = client.receiveJson(); // get edited CSV file and changelist
    const size_t changes = responseJson.at("changes");
    const size_t deletes = responseJson.at("deletes");

    std::cout << "changes: " << changes << std::endl;
    std::cout << "deletes: " << deletes << std::endl;

    //-------------------------------------------------------- parse and save received Csv     !!!!!! (code duplication)

    std::cout << "----------------------" << std::endl;
    const std::string fileName = responseJson.at("fileName").get<std::string>();

    std::ostringstream csvStream; // store csv data

    // fill csv data
    const auto &csvData = responseJson.at("csvData");
    for (const auto &row: csvData) {
        for (size_t col = 0; col < row.size(); ++col) {
            csvStream << row[col];
            if (col < row.size() - 1) {
                csvStream << ",";
            }
        }
        csvStream << "\n";
    }

    // move string data to Document
    std::istringstream csvInputStream(csvStream.str());
    rapidcsv::Document doc(csvInputStream, rapidcsv::LabelParams(-1, -1)); // no-headers

    doc.Save(std::format("{}_received", fileName));
    //--------------------------------------------------------

    client.close();

    return 0;
}
