#include "fix_client.h"
#include "application.h"
#include "quickfix/FileStore.h"
#include "quickfix/Session.h"
#include <iostream>

FixClient::FixClient(const std::string & setting_file) {
    const FIX::SessionSettings settings(setting_file);
    Application application;
    FIX::FileStoreFactory file_store_factory(settings);
    _session_setting = std::make_shared<FIX::SessionSettings>(settings);
    _initiator = std::unique_ptr<FIX::Initiator>(new FIX::SocketInitiator(application, file_store_factory, *_session_setting));
}

FixClient::~FixClient() = default;

void FixClient::connect() {
    _initiator->start();
    std::cout << "Connected to EduX" << std::endl;
    _is_connected = true;
}

void FixClient::disconnect() {
    _initiator->stop();
    std::cout << "Disconnected from EduX" << std::endl;
    _is_connected = false;
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
    std::set<FIX::SessionID> sessions = _session_setting->getSessions();
    if (sessions.empty()) {
        throw std::runtime_error("No sessions configured");
    }

    return *sessions.begin();
}

