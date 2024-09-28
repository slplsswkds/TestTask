cmake_minimum_required(VERSION 3.29)
project(TestTask)

add_compile_options(-std=gnu++2b -D__cpp_concepts=202002L)

find_package(CLI11 CONFIG REQUIRED) # cli args parser
find_package(Boost REQUIRED )       # boost.asio for networking

add_executable(Client client/client.cpp
        client/cli/CliArgs.cpp
        client/cli/CliArgs.h
        client/csv_utils/CsvHandler.cpp
        client/csv_utils/CsvHandler.h
        client/networking/TcpClient.cpp
        client/networking/TcpClient.h
        csvRxTx/CsvRxTx.cpp
        csvRxTx/CsvRxTx.h)

add_executable(Server server/server.cpp
        server/networking/TcpServer.cpp
        server/networking/TcpServer.h
        server/networking/ClientHandler.cpp
        server/networking/ClientHandler.h
)

target_link_libraries(Client CLI11::CLI11 stdc++)

target_link_libraries(Server stdc++)