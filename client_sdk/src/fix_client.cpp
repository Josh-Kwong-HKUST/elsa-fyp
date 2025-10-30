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

bool FixClient::is_connected() const {
    const bool res = _is_connected.load(std::memory_order_relaxed);
    if (!res) {
        std::cerr << "Not connected to FIX server" << std::endl;
    }
    return res;
}

bool FixClient::submit_market_order(const std::string &ticker, const double &quantity, const OrderSide &side, const std::string& custom_order_id) const {
    if (!is_connected()) return false;
    try {
        FIX42::NewOrderSingle new_order_fix_message = create_new_order_fix_request(ticker, quantity, side, custom_order_id);
        FIX::Session::sendToTarget(new_order_fix_message, get_session_id());
        std::cout << "[FixClient] Market Order submitted: " << new_order_fix_message << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[FixClient] Failed to submit market order: " << e.what() << std::endl;
        return false;
    }
}

bool FixClient::submit_limit_order(const std::string &ticker, const double &price, const double &quantity, const OrderSide &side, const TimeInForce& time_in_force, const std::string& custom_order_id) const {
    if (!is_connected()) return false;
    try {
        std::cout << "[FixClient] Submitting limit order: " << (side == OrderSide::BUY ? "BUY " : "SELL ") << quantity << " " << ticker << "@" << price << std::endl;
        FIX42::NewOrderSingle new_order_fix_message = create_new_order_fix_request(ticker, quantity, side, custom_order_id);
        char tif;
        if (time_in_force == TimeInForce::GTC) {
            tif = FIX::TimeInForce_GOOD_TILL_CANCEL;
        } else {
            throw std::invalid_argument("Only GTC is supported for limit order currently!");
        }
        new_order_fix_message.set(FIX::TimeInForce(tif));
        // leave price check for server side
        new_order_fix_message.set(FIX::Price(price));

        FIX::Session::sendToTarget(new_order_fix_message, get_session_id());
        std::cout << "[FixClient] Limit Order submitted: " << new_order_fix_message << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[FixClient] Failed to submit limit order: " << e.what() << std::endl;
        return false;
    }
}

bool FixClient::cancel_order(const std::string& ticker, const OrderSide& side, const std::string &custom_order_id) const {
    if (!is_connected()) return false;
    try {
        FIX42::OrderCancelRequest cancel_request = create_cancel_order_fix_request(ticker, side, custom_order_id);
        FIX::Session::sendToTarget(cancel_request, get_session_id());
        std::cout << "[FixClient] Cancel order request submitted: " << cancel_request << std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[FixClient] Failed to cancel order: " << e.what() << std::endl;
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


