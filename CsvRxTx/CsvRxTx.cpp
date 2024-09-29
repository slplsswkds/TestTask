#include "CsvRxTx.h"

CsvRxTx::CsvRxTx(boost::asio::ip::tcp::socket socket) : socket_(std::move(socket)) {
}

void CsvRxTx::transmitCsv() {
    try {
        std::stringstream csvFileStream;
        docCsv_.Save(csvFileStream); // Save CSV to stream

        std::string fileData = csvFileStream.str(); // Get string with data
        boost::asio::write(socket_, boost::asio::buffer(fileData)); // Send file data
        std::cout << "File sent successfully. Total size: " << fileData.size() << " bytes." << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error while sending file: " << e.what() << std::endl;
    }
}

void CsvRxTx::receiveCsv() {
    boost::asio::streambuf streamBuffer;
    boost::system::error_code error;

    boost::asio::read(socket_, streamBuffer, boost::asio::transfer_at_least(1), error);
    if (error && error != boost::asio::error::eof) {
        std::cerr << "Error during file reception: " << error.message() << std::endl;
        return;
    }

    std::stringstream fileData;
    fileData << &streamBuffer; // Move file data
    rapidcsv::Document doc(fileData, rapidcsv::LabelParams(0, 0));
    docCsv_ = doc; // Save csv file to the class field

    std::cout << "File received successfully. Total size: " << fileData.str().size() << " bytes." << std::endl;
}
