#ifndef ELSA_FYP_CLIENT_SDK_FIX_CLIENT_H
#define ELSA_FYP_CLIENT_SDK_FIX_CLIENT_H

#include <memory>
#include <string>

#include "order.h"
#include "quickfix/SocketInitiator.h"
#include "quickfix/Application.h"

class FixClient final : FIX::Application {
private:
    std::unique_ptr<FIX::Initiator> _initiator;
    std::atomic_bool _is_connected = false;

public:
    explicit FixClient(const std::string&);
    void connect(const int&) const;
    void disconnect();
    bool is_connected() const;
    [[nodiscard]] FIX::SessionID get_session_id() const;
    // methods to interact with market
    bool submit_market_order(const std::string&, const double&, const OrderSide&, const std::string& = "") const;
    bool submit_limit_order(const std::string&, const double&, const double&, const OrderSide&, const TimeInForce&, const std::string& = "") const;

private:
    void onCreate(const FIX::SessionID &) override {};
    void onLogon(const FIX::SessionID &) override {
        std::cout << "[FixClient] Connected to EduX" << std::endl;
        _is_connected.store(true);
    };
    void onLogout(const FIX::SessionID &) override {
        std::cout << "[FixClient] Disconnected from EduX" << std::endl;
        _is_connected.store(false);
    };
    void toAdmin(FIX::Message &, const FIX::SessionID &) override {}
    void toApp(FIX::Message &, const FIX::SessionID &) override {};
    void fromAdmin(const FIX::Message & msg, const FIX::SessionID & session_id) override {
        std::cout << "[FixClient] fromAdmin:" << msg << "from session " << session_id << std::endl;
    };
    void fromApp(const FIX::Message &msg, const FIX::SessionID &session_id) override {
        std::cout << "[FixClient] fromApp:" << msg << "from session " << session_id << std::endl;
    };
};

#endif //ELSA_FYP_CLIENT_SDK_FIX_CLIENT_H