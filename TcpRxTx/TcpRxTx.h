#pragma once

#include "../rapidcsv/rapidcsv.h"
#include "boost/asio.hpp"
#include <nlohmann/json.hpp>

class TcpRxTx {
protected:
    TcpRxTx(boost::asio::ip::tcp::socket socket);

    boost::asio::ip::tcp::socket socket_;

public:
    void transmitJson(const nlohmann::json &json); // send Json message to the socket target
    nlohmann::json receiveJson(); // receive Json from the socket target
};
