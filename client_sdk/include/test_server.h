#pragma once
#include <quickfix/Application.h>
#include <iostream>

class TestFixServer final : public FIX::Application {
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
        std::cout << "[Server] fromAdmin:" << msg << "from session " << session_id << std::endl;
    };
    void fromApp(const FIX::Message &msg, const FIX::SessionID &session_id) override {
        std::cout << "[Server] Received message from application" << std::endl;
        std::cout << "[Server] fromApp:" << msg << "from session " << session_id << std::endl;
    };
};