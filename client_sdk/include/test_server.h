#pragma once
#include "quickfix/Application.h"
#include "quickfix/fix42/MessageCracker.h"
#include "quickfix/fix42/OrderCancelRequest.h"
#include "quickfix/fix42/NewOrderSingle.h"
#include <iostream>
#include "quickfix/Session.h"
#include "quickfix/fix42/ExecutionReport.h"
#include "quickfix/fix42/OrderCancelReject.h"

class TestFixServer final : public FIX::Application, FIX42::MessageCracker {
public:
    void onCreate(const FIX::SessionID &) override {};
    void onLogon(const FIX::SessionID &) override {
        std::cout << "[Server] logon received" << std::endl;
    };
    void onLogout(const FIX::SessionID &) override {
        std::cout << "[Server] logout received" << std::endl;
    };
    void toAdmin(FIX::Message &, const FIX::SessionID &) override {}
    void toApp(FIX::Message &, const FIX::SessionID &) override {};
    void fromAdmin(const FIX::Message & msg, const FIX::SessionID & session_id) override {
        crack(msg, session_id);
    };
    void fromApp(const FIX::Message &msg, const FIX::SessionID &session_id) override {
        crack(msg, session_id);
    };

private:
    void onMessage( const FIX42::NewOrderSingle& new_order, const FIX::SessionID& session_id) override {
        std::cout << "[Server] received new order request:\n" << new_order << "\nfrom session: " << session_id << std::endl;
        FIX42::ExecutionReport execution_report;

        FIX::Session::sendToTarget(execution_report, session_id);
    }
    void onMessage( const FIX42::OrderCancelRequest& cancel_request, const FIX::SessionID& session_id) override {
        std::cout << "[Server] received cancel order request:\n" << cancel_request << "\nfrom session: " << session_id << std::endl;
    }
};
