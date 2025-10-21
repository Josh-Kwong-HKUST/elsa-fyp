#ifndef ELSA_FYP_CLIENT_SDK_APPLICATION_H
#define ELSA_FYP_CLIENT_SDK_APPLICATION_H

#include <quickfix/Application.h>

class Application final : public FIX::NullApplication {
    // void onCreate(const FIX::SessionID &) override;
    // void onLogon(const FIX::SessionID &) override;
    // void onLogout(const FIX::SessionID &) override;
    // void toAdmin(FIX::Message &, const FIX::SessionID &) override;
    // void toApp(FIX::Message &, const FIX::SessionID &) override;
    // void fromAdmin(const FIX::Message &, const FIX::SessionID &) override;
    // void fromApp(const FIX::Message &, const FIX::SessionID &) override;
};

#endif //ELSA_FYP_CLIENT_SDK_APPLICATION_H