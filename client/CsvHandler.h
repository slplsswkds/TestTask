#ifndef CSVHANDLER_H
#define CSVHANDLER_H

#include <expected>
#include <random>
#include <filesystem>
#include "../rapidcsv/rapidcsv.h"

class CsvHandler {
public:
    static auto createCsv() -> std::expected<rapidcsv::Document, std::string>;

    static auto genRandDataString() -> std::string;

    static auto saveCsv(rapidcsv::Document csvFile,
                        const std::filesystem::path &path) -> std::expected<void, std::string>;
};

#endif //CSVHANDLER_H
