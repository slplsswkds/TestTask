#ifndef CLIARGS_H
#define CLIARGS_H

#include <filesystem>
#include <CLI/CLI.hpp>
#include <regex>

#define DEFAULT_PORT "4666"

class CliArgs {
public:
    int parse_cli_args(int argc, const char **argv); /// Parse command line arguments.

    auto getFilename() const -> std::filesystem::path;

    auto getTargetIp() const -> std::string;

    auto getTargetPort() const -> uint16_t;

    void setFileName(const std::filesystem::path &path);

    void setTargetIp(const std::string &ipV4);

    void setTargetPort(uint16_t port);

private:
    void setup_parser(); /// configure cli args parser
    CLI::App clientCliArgs; /// parser for cli

    std::filesystem::path filename; /// Output file name
    std::string ipv4_address; /// server ip
    uint16_t port; /// server port
};


#endif //CLIARGS_H
