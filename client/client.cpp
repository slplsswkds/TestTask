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

    // generating CSV file
    auto csvDocGenerated = CsvGenerator::createCsv();

    // Saving CSV file
    csvDocGenerated.Save(args.getFilename());

    auto socket = connect(args.getTargetIp(), args.getTargetPort());
    if (!socket.is_open()) {
        std::cerr << "Cannot estable connection with server" << std::endl;
        return 1;
    }

    auto client = TcpConnection(std::move(socket));
    auto csvWrapper = CsvWrapper(args.getFilename(), csvDocGenerated); // for serialize/deserialize JSON messages

    // send the file to the server
    client.transmitJson(csvWrapper.serializeToJson());

    // Receive the file edited by the server
    auto wrapper = CsvWrapper::deserializeFromJson(client.receiveJson());

    // save received CSV file to the disk
    wrapper.csvDoc_.Save(std::format("received_{}", wrapper.fileName_));

    // Print changelist
    if (wrapper.changed_.has_value() && wrapper.deleted_.has_value()) {
        std::cout << "changes: " << wrapper.changed_.value() << std::endl;
        std::cout << "deletes: " << wrapper.deleted_.value() << std::endl;
    }

    client.close();

    return 0;
}
