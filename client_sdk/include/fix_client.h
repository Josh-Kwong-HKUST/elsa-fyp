#ifndef ELSA_FYP_CLIENT_SDK_FIX_CLIENT_H
#define ELSA_FYP_CLIENT_SDK_FIX_CLIENT_H

#include <memory>
#include <string>

#include "order.h"
#include "quickfix/SocketInitiator.h"

class FixClient {
private:
    std::unique_ptr<FIX::Initiator> _initiator;
    std::shared_ptr<FIX::SessionSettings> _session_setting;
    bool _is_connected = false;

public:
    explicit FixClient(const std::string&);
    ~FixClient();
    void connect();
    void disconnect();
    FIX::SessionID get_session_id() const;
    // methods to interact with market
    bool submit_order(const Order& order) const;
};

#endif //ELSA_FYP_CLIENT_SDK_FIX_CLIENT_H