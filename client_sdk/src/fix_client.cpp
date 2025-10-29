#include "fix_client.h"

#include <chrono>

#include "quickfix/FileStore.h"
#include "quickfix/Session.h"
#include <iostream>
#include <thread>

FixClient::FixClient(const std::string & setting_file): Application() {
    const FIX::SessionSettings settings(setting_file);
    FIX::FileStoreFactory file_store_factory(settings);
    _initiator = std::unique_ptr<FIX::Initiator>(new FIX::SocketInitiator(*this, file_store_factory, settings));
}

FixClient::~FixClient() = default;

void FixClient::connect(const int& timeout_sec) const {
    std::cout << "Connecting to EduX..." << std::endl;
    _initiator->start();
    std::chrono::seconds timeout(timeout_sec);
    auto start = std::chrono::steady_clock::now();
    while (!_is_connected.load(std::memory_order_relaxed)) {
        auto now = std::chrono::steady_clock::now();
        if (now - start > timeout) {
            throw std::runtime_error("Connection timed out");
        }
        // sleep shortly to prevent spinning
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void FixClient::disconnect() {
    _initiator->stop();
    std::cout << "Disconnected from EduX" << std::endl;
    _is_connected.store(false);
}

bool FixClient::submit_order(const Order& order) const {
    if (!_is_connected) {
        std::cerr << "Not connected to FIX server" << std::endl;
        return false;
    }

    try {
        FIX42::NewOrderSingle newOrder = order.convert_to_fix_new_order_message();

        FIX::Session::sendToTarget(newOrder, get_session_id());
        std::cout << "Order submitted: " << order.symbol << " "
                  << (order.side == OrderSide::BUY ? "BUY" : "SELL") << " "
                  << order.quantity << std::endl;

        return true;
    } catch (const std::exception& e) {
        std::cerr << "Failed to submit order: " << e.what() << std::endl;
        return false;
    }
}

FIX::SessionID FixClient::get_session_id() const {
    // Get the first session from settings
    std::set<FIX::SessionID> sessions = _initiator->getSessions();
    if (sessions.empty()) {
        throw std::runtime_error("No sessions configured");
    }

    return *sessions.begin();
}

