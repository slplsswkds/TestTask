#pragma once

#include "boost/asio.hpp"
#include <nlohmann/json.hpp>
#include "../rapidcsv/rapidcsv.h"

class TcpRxTx {
protected:
    explicit TcpRxTx(boost::asio::ip::tcp::socket socket);

    boost::asio::ip::tcp::socket socket_;

public:
    void transmitJson(const nlohmann::json &json); // send Json message to the socket target
    nlohmann::json receiveJson(); // receive Json from the socket target
};

/// CsvWrapper. Class for serialize and deserialize json message with file.
class CsvWrapper {
public:
    explicit CsvWrapper(const std::string &fileName);
    explicit CsvWrapper(const std::string &fileName, const rapidcsv::Document &csvDoc);

    nlohmann::json serializeToJson() const;

    static CsvWrapper deserializeFromJson(const nlohmann::json &jsonData);

private:
    std::string fileName_;
    rapidcsv::Document csvDoc_;
};
