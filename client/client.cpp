#include "CliArgs.h"
#include "print"

int main(const int argc, const char **argv) {
    CliArgs args;
    args.parse_cli_args(argc, argv);

    std::cout << args.getFilename() << std::endl;
    std::cout << args.getTargetIp() << std::endl;
    std::cout << args.getTargetPort() << std::endl;

    return 0;
}
