#include "../client_sdk/include/fix_client.h"
#include "../client_sdk/include/test_server.h"
#include "../client_sdk/include/order.h"
#include <quickfix/SessionSettings.h>
#include <quickfix/FileStore.h>
#include <quickfix/SocketAcceptor.h>
#include <iostream>

int main() {
    const FIX::SessionSettings settings("/home/josh/repo/elsa-fyp/client_sdk/example_config_server.cfg");
    TestFixServer server;
    FIX::FileStoreFactory file_store_factory(settings);
    FIX::SocketAcceptor acceptor(server, file_store_factory, settings);
    acceptor.start();
    std::cout << "Server started" << std::endl;

    const auto client = new FixClient("/home/josh/repo/elsa-fyp/client_sdk/example_config_client.cfg");
    client->connect();
    client->submit_order(Order("test_ticker", 1.0, 10.0, OrderSide::BUY, OrderType::LIMIT, TimeInForce::GTC));
    std::cout << "Client started" << std::endl;
    std::cout << "Enter any key to exit" << std::endl;
    std::cin.ignore();
    acceptor.stop();
    client->disconnect();
}