#include "../client_sdk/include/test_server.h"
#include "../client_sdk/include/order.h"
#include <quickfix/SessionSettings.h>
#include <quickfix/FileStore.h>
#include <quickfix/SocketAcceptor.h>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem

#include "test_client.h"

int main() {
    fs::path serverConfigFileName = "example_config_server.cfg";
    fs::path pathToServerConfig = fs::current_path().parent_path() / fs::path("client_sdk") / configFileName;
    const FIX::SessionSettings settings(pathToServerConfig.string());
    TestFixServer server;
    FIX::FileStoreFactory file_store_factory(settings);
    FIX::SocketAcceptor acceptor(server, file_store_factory, settings);
    acceptor.start();
    std::cout << "Server started" << std::endl;

    fs::path clientConfigFileName = "example_config_client.cfg";
    fs::path pathToClientConfig = fs::current_path().parent_path() / fs::path("client_sdk") / configFileName;
    const auto client = new TestClient(pathToClientConfig.string());
    client->connect(5);
    bool res = client->submit_limit_order("test_ticker", 1.0, 10.0, OrderSide::BUY, TimeInForce::GTC, "joshorder");
    bool res1 = client->cancel_order("test_ticker", OrderSide::BUY, "joshorder");
    std::cout << "Client started" << std::endl;
    std::cout << "Enter any key to exit" << std::endl;
    std::cin.ignore();
    acceptor.stop();
    client->disconnect();
    delete client;
}
