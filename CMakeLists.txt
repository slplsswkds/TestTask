cmake_minimum_required(VERSION 3.29)
project(TestTask)

set(CMAKE_CXX_STANDARD 23)
cmake_policy(SET CMP0167 NEW)

find_package(CLI11 CONFIG REQUIRED) # cli args parser
find_package(Boost REQUIRED)       # boost.asio for networking
find_package(nlohmann_json REQUIRED)

add_executable(Client client/client.cpp
        client/cli/CliArgs.cpp
        client/cli/CliArgs.h
        client/csv_utils/CsvGenerator.cpp
        client/csv_utils/CsvGenerator.h
        client/networking/TcpConnection.cpp
        client/networking/TcpConnection.h
        TcpRxTx/TcpRxTx.cpp
        TcpRxTx/TcpRxTx.h)

add_executable(Server server/server.cpp
        server/networking/TcpServer.cpp
        server/networking/TcpServer.h
        server/networking/ClientHandler.cpp
        server/networking/ClientHandler.h
        TcpRxTx/TcpRxTx.cpp
        TcpRxTx/TcpRxTx.h
)

target_link_libraries(Client CLI11::CLI11 stdc++ nlohmann_json::nlohmann_json)

target_link_libraries(Server stdc++ nlohmann_json::nlohmann_json)
