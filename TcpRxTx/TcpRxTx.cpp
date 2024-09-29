#include "TcpRxTx.h"

#include <iostream>

TcpRxTx::TcpRxTx(boost::asio::ip::tcp::socket socket) : socket_(std::move(socket)) {
}

void TcpRxTx::transmitJson(const nlohmann::json &json) {
    std::string json_data = json.dump(); // convert json to string

    uint32_t data_size = json_data.size();
    boost::system::error_code error;

    // send string size
    boost::asio::write(socket_, boost::asio::buffer(&data_size, sizeof(data_size)), error);
    if (error) {
        throw boost::system::system_error(error);
    }

    // send message
    boost::asio::write(socket_, boost::asio::buffer(json_data), error);
    if (error) {
        throw boost::system::system_error(error);
    }
}


nlohmann::json TcpRxTx::receiveJson() {
    uint32_t data_size = 0;
    boost::system::error_code error;

    // receive input message length
    boost::asio::read(socket_, boost::asio::buffer(&data_size, sizeof(data_size)), error);
    if (error) {
        throw boost::system::system_error(error);
    }

    // prepare buffer for reading accepted data
    std::vector<char> buffer(data_size);

    // read data to buffer
    boost::asio::read(socket_, boost::asio::buffer(buffer.data(), data_size), error);
    if (error) {
        throw boost::system::system_error(error);
    }

    // convert data to string and pare into JSON
    std::string response_data(buffer.data(), data_size);
    const nlohmann::json response = nlohmann::json::parse(response_data);

    std::cout << "received json: " << response.dump(4) << std::endl;
    return response;
}


//--------------------------------------------------

CsvWrapper::CsvWrapper(const std::string &fileName) : fileName_(fileName) {
}

CsvWrapper::CsvWrapper(const std::string &fileName, const rapidcsv::Document &csvDoc) : fileName_(fileName),
    csvDoc_(csvDoc) {
}

nlohmann::json CsvWrapper::serializeToJson() const {
    nlohmann::json jsonData;
    jsonData["fileName"] = fileName_;

    std::vector<std::vector<std::string> > csvData; // Serialize CSV content as 2D array

    const size_t rowCount = csvDoc_.GetRowCount();
    const size_t columnCount = csvDoc_.GetColumnCount();

    // fill array by data
    for (size_t row = 0; row < rowCount; ++row) {
        std::vector<std::string> rowData;
        for (size_t col = 0; col < columnCount; ++col) {
            rowData.push_back(csvDoc_.GetCell<std::string>(col, row));
        }
        csvData.push_back(rowData);
    }

    if (changed_.has_value() && deleted_.has_value()) {
        jsonData["changes"] = changed_.value();
        jsonData["deletes"] = changed_.value();
    }

    jsonData["csvData"] = csvData;
    return jsonData;
}

CsvWrapper CsvWrapper::deserializeFromJson(const nlohmann::json &jsonData) {
    const std::string fileName = jsonData.at("fileName").get<std::string>();

    std::ostringstream csvStream; // store csv data

    // fill csv data
    const auto &csvData = jsonData.at("csvData");
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
    rapidcsv::Document doc(csvInputStream, rapidcsv::LabelParams(-1, -1)); // Якщо немає заголовків

    CsvWrapper wrapper(fileName, doc);

    try {
        const uint changes = jsonData.at("changes");
        const uint deletes = jsonData.at("deletes");

        wrapper.changed_ = changes;
        wrapper.deleted_ = deletes;
    } catch (const std::exception &e) {
        // json have not this fields
    }


    return wrapper;
}
