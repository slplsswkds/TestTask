#include "TcpRxTx.h"

TcpRxTx::TcpRxTx(boost::asio::ip::tcp::socket socket) : socket_(std::move(socket)) {
}

void TcpRxTx::transmitJson(const nlohmann::json &json) {
    boost::system::error_code error;
    boost::asio::write(socket_, boost::asio::buffer(json.dump()), error);

    if (error) {
        throw boost::system::system_error(error);
    }
}

nlohmann::json TcpRxTx::receiveJson() {
    char buffer[1024];
    boost::system::error_code error;
    const size_t length = socket_.read_some(boost::asio::buffer(buffer), error);
    std::string response_data(buffer, length);

    const nlohmann::json response = nlohmann::json::parse(response_data);
    std::cout << "received json: " << response.dump(4) << std::endl;

    return response;
}
