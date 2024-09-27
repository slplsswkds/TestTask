cmake_minimum_required(VERSION 3.29)
project(Client)

#set(CMAKE_CXX_STANDARD 23)
add_compile_options(-std=gnu++2b -D__cpp_concepts=202002L)

add_executable(Client client.cpp
        CliArgs.cpp
        CliArgs.h)

find_package(CLI11 CONFIG REQUIRED) # cli args parser
find_package(Boost REQUIRED )       # boost.asio for networking

target_link_libraries(Client CLI11::CLI11)
target_link_libraries(Client stdc++)