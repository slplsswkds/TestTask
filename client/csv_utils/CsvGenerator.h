#ifndef CSVHANDLER_H
#define CSVHANDLER_H

#include <random>
#include "../../rapidcsv/rapidcsv.h"

class CsvGenerator {
public:
    static auto createCsv() -> rapidcsv::Document;
    static auto genRandDataString() -> std::string;
};

#endif //CSVHANDLER_H
