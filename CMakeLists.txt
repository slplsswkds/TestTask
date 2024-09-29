cmake_minimum_required(VERSION 3.29)
project(TestTask)

set(CMAKE_CXX_STANDARD 23)
cmake_policy(SET CMP0167 NEW)

find_package(CLI11 CONFIG REQUIRED) # CLI args parser
find_package(Boost REQUIRED COMPONENTS system log log_setup)
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
        server/logging/logging.cpp
        server/logging/logging.h)

target_link_libraries(Client
        stdc++
        CLI11::CLI11
        nlohmann_json::nlohmann_json
        Boost::system
        Boost::log
        Boost::log_setup)

target_link_libraries(Server
        stdc++
        nlohmann_json::nlohmann_json
        Boost::system
        Boost::log
        Boost::log_setup)
