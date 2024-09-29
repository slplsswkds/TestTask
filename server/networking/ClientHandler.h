#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <boost/asio.hpp>
#include "../../TcpRxTx/TcpRxTx.h"
#include "../../rapidcsv/rapidcsv.h"

class Changelist {
public:
    Changelist(size_t changes, size_t deletes);

    size_t changes_; /// count changes in the file
    size_t deletes_; /// count deletes in the file
};

class ClientHandler : public TcpRxTx {
public:
    explicit ClientHandler(boost::asio::ip::tcp::socket socket);

    void handle();

private:
    rapidcsv::Document docCsv_;

    // edits the resulting file, saves it in the file field, and returns changelist
    auto editFile() -> Changelist;
};

#endif //CLIENTHANDLER_H
