cmake_minimum_required(VERSION 3.29)
project(Server)

set(CMAKE_CXX_STANDARD 23)

add_executable(Server server.cpp
        TcpServer.cpp
        TcpServer.h)

find_package(Boost REQUIRED)       # boost.asio for networking

target_link_libraries(Server stdc++)