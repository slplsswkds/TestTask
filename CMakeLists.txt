cmake_minimum_required(VERSION 3.29)
project(TestTask)

set (CMAKE_CXX_STANDARD 23)

find_package(CLI11 CONFIG REQUIRED) # cli args parser
find_package(Boost REQUIRED )       # boost.asio for networking

add_executable(Client client/client.cpp
        client/cli/CliArgs.cpp
        client/cli/CliArgs.h
        client/csv_utils/CsvGenerator.cpp
        client/csv_utils/CsvGenerator.h
        client/networking/TcpConnection.cpp
        client/networking/TcpConnection.h
        CsvRxTx/CsvRxTx.cpp
        CsvRxTx/CsvRxTx.h)

add_executable(Server server/server.cpp
        server/networking/TcpServer.cpp
        server/networking/TcpServer.h
        server/networking/ClientHandler.cpp
        server/networking/ClientHandler.h
        CsvRxTx/CsvRxTx.cpp
        CsvRxTx/CsvRxTx.h
)

target_link_libraries(Client CLI11::CLI11 stdc++)

target_link_libraries(Server stdc++)