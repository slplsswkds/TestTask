#include "ClientHandler.h"

#include <iostream>
#include <ranges>
#include <random>
#include <fstream>

ClientHandler::ClientHandler(boost::asio::ip::tcp::socket socket)
    : CsvRxTx(std::move(socket), rapidcsv::Document()) {}

void ClientHandler::handle() {
    receiveCsv();
    editFile(); // Assuming you will implement editFile() later
    transmitCsv();
    sendChangelist();
}

// void ClientHandler::receiveFile() {
//     boost::asio::streambuf streamBuffer;
//     std::ostream outputStream(&streamBuffer);
//
//     boost::system::error_code error;
//     boost::asio::read(socket_, streamBuffer, boost::asio::transfer_at_least(1), error);
//
//     if (error && error != boost::asio::error::eof) {
//         std::cerr << "Error during file reception: " << error.message() << std::endl;
//     } else if (streamBuffer.size() == 0) {
//         std::cerr << "The file was not received: buffer is empty" << std::endl;
//     } else {
//         std::stringstream fileData;
//         fileData << &streamBuffer; // move file data
//
//         rapidcsv::Document doc(fileData, rapidcsv::LabelParams(0, 0));
//         this->file_ = doc; // save csv file to the class field
//
//         std::cout << "File received successfully. Total size: " << fileData.str().size() << " bytes." << std::endl;
//     }
// }

void ClientHandler::editFile() {
}

// void ClientHandler::sendFile() {
//     try {
//         // converting CSV into string stream
//         std::stringstream csvFileStream;
//         this->file_.Save(csvFileStream); // save CSV to stream
//
//         std::string fileData = csvFileStream.str(); // get string with data
//
//         // send file data
//         boost::asio::write(socket_, boost::asio::buffer(fileData));
//         std::cout << "File sent successfully. Total size: " << fileData.size() << " bytes." << std::endl;
//     } catch (const std::exception &e) {
//         std::cerr << "Error while sending file: " << e.what() << std::endl;
//     }
// }

void ClientHandler::sendChangelist() {
}
