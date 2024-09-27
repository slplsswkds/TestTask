//
// Created by maks on 9/27/24.
//

#include "CliArgs.h"

int CliArgs::parse_cli_args(int argc, const char **argv) {
    this->setup_parser();
    CLI11_PARSE(this->clientCliArgs, argc, argv);
    return 0;
}

auto CliArgs::getFilename() const -> std::filesystem::path {
    return this->filename;
}

auto CliArgs::getTargetIp() const -> std::string {
    return this->ipv4_address;
}

auto CliArgs::getTargetPort() const -> uint16_t {
    return this->port;
}

void CliArgs::setFileName(const std::filesystem::path &path) {
    this->filename = path.filename();
}

void CliArgs::setTargetIp(const std::string &ipV4) {
    this->ipv4_address = ipV4;
}

void CliArgs::setTargetPort(const uint16_t port) {
    this->port = port;
}

void CliArgs::setup_parser() {
    /// Lambda expression for checking the passed IPv4 address
    auto check_ipv4 = [](const std::string &ip_string) {
        const std::regex ipv4Regex(
            R"(^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$)"
        );
        if (!std::regex_match(ip_string, ipv4Regex)) {
            std::cerr << ("Invalid IPv4 address format") << std::endl;
        }
        return std::string();
    };

    /// parser for filename
    this->clientCliArgs
            .add_option("-f,--filename", this->filename)
            ->required();

    /// parser for ipv4
    this->clientCliArgs
            .add_option("-i, --ip", this->ipv4_address, "target ip")
            ->default_val("127.0.0.1")
            ->check(check_ipv4);

    /// parser for port
    this->clientCliArgs
            .add_option("-p, --port", this->port, "target port")
            ->expected(0, 65535)
            ->default_val(DEFAULT_PORT);
}
