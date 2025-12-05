#include "../client_sdk/include/order.h"
#include <quickfix/SessionSettings.h>
#include <quickfix/FileStore.h>
#include <quickfix/SocketAcceptor.h>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

#include "test_client.h"

int main()
{
    fs::path clientConfigFileName = "example_config_client.cfg";
    fs::path pathToClientConfig = fs::current_path() / clientConfigFileName;
    std::cout << "Path to config: " << pathToClientConfig << std::endl;
    const auto client = new TestClient(pathToClientConfig.string());
    client->connect(5);
    int current_order_id = 1;
    while (true)
    {
        std::cout << "Submit order or cancel? (N/C)" << std::endl;
        char action;
        std::cin >> action;
        if (action == 'c' || action == 'C') {
            std::string order_id_to_cancel;
            std::cout << "Enter the Order ID to cancel: ";
            std::cin >> order_id_to_cancel;
            client->cancel_order("test_ticker", OrderSide::BUY, order_id_to_cancel);
            client->cancel_order("test_ticker", OrderSide::SELL, order_id_to_cancel);
            continue; // Skip incrementing order ID for cancel action
        }

        std::cout << "You may BUY or SELL test_ticker only." << std::endl;
        std::cout << "Enter B to BUY, S to SELL, Q to QUIT, C to cancel:";
        std::cin >> action;

        std::cout << "Enter order quantity in integers: ";
        int quantity;
        std::cin >> quantity;

        std::cout << "Enter price in integers: ";
        int price;
        std::cin >> price;

        if (action == 'Q' || action == 'q')
        {
            break;
        }
        else if (action == 'B' || action == 'b')
        {
            client->submit_limit_order("test_ticker", price, quantity, OrderSide::BUY, TimeInForce::GTC, std::to_string(current_order_id));
        }
        else if (action == 'S' || action == 's')
        {
            client->submit_limit_order("test_ticker", price, quantity, OrderSide::SELL, TimeInForce::GTC, std::to_string(current_order_id));
        }
        else
        {
            std::cout << "Invalid action. Please try again." << std::endl;
            continue;
        }
        ++current_order_id;
    }
    client->disconnect();
    delete client;
}
