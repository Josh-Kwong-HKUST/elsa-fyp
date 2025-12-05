#ifndef GATEWAY_APPLICATION_H
#define GATEWAY_APPLICATION_H

#include <iostream>
#include <queue>

#include "quickfix/Application.h"
#include "quickfix/MessageCracker.h"
#include "quickfix/Mutex.h"
#include "quickfix/Utility.h"
#include "quickfix/Values.h"

#include "quickfix/fix42/NewOrderSingle.h"
#include "quickfix/fix42/OrderCancelRequest.h"

#include "../../matching_engine/src/order.h"
#include "../../matching_engine/src/limit_order_book.h"
#include "id_generator.h"

class Application : public FIX::Application, public FIX::MessageCracker
{
    // Application overloads
    void onCreate(const FIX::SessionID &) {}
    void onLogon(const FIX::SessionID &sessionID);
    void onLogout(const FIX::SessionID &sessionID);
    void toAdmin(FIX::Message &, const FIX::SessionID &) {}
    void toApp(FIX::Message &, const FIX::SessionID &) EXCEPT(FIX::DoNotSend) {}
    void fromAdmin(const FIX::Message &, const FIX::SessionID &)
        EXCEPT(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon) {}
    void fromApp(const FIX::Message &message, const FIX::SessionID &sessionID)
        EXCEPT(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType);

    // MessageCracker overloads
    void onMessage(const FIX42::NewOrderSingle &, const FIX::SessionID &);
    void onMessage(const FIX42::OrderCancelRequest &, const FIX::SessionID &);

    // Order functionality
    void processOrder(const Order &);
    void processCancel(int orderId, const std::string &symbol, Side);

    void updateOrder(const Order &, char status);
    void rejectOrder(const Order &order) { updateOrder(order, FIX::OrdStatus_REJECTED); }
    void acceptOrder(const Order &order) { updateOrder(order, FIX::OrdStatus_NEW); }
    void fillOrder(const Order &order)
    {
        // TODO: We currently can't detect 0 fills
        updateOrder(order, order.get_quantity() == 0 ? FIX::OrdStatus_FILLED : FIX::OrdStatus_PARTIALLY_FILLED);
    }
    void cancelOrder(const Order &order) { updateOrder(order, FIX::OrdStatus_CANCELED); }

    void rejectOrder(
        const FIX::SenderCompID &,
        const FIX::TargetCompID &,
        const FIX::ClOrdID &clOrdID,
        const FIX::Symbol &symbol,
        const FIX::Side &side,
        const std::string &message);

    Side convert(const FIX::Side &); // FIX to internal
    FIX::Side convert(Side);         // internal to FIX

    IDGenerator idGenerator;

public:
    LimitOrderBook limitOrderBook;

};
#endif