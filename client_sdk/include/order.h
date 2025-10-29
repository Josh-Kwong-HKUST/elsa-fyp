#ifndef ELSA_FYP_CLIENT_SDK_ORDER_H
#define ELSA_FYP_CLIENT_SDK_ORDER_H

#include <string>
#include "quickfix/fix42/NewOrderSingle.h"

enum class OrderSide {
    BUY = 1,
    SELL = 2
};

enum class OrderType {
    MARKET = 1,
    LIMIT = 2,
    STOP = 3
};

enum class TimeInForce {
    GTC = 0,  // Good Till Cancel
    IOC = 1   // Immediate or Cancel, todo: add more Time in Force
};

struct Order {
    std::string symbol;
    OrderSide side;
    OrderType order_type;
    double quantity;
    double price;
    std::string custom_order_id;  // custom id for client's reference only
    TimeInForce time_in_force;

    Order(const std::string& symbol, const double px, const double qty, const OrderSide side, const OrderType order_type, const TimeInForce time_in_force)
        : symbol(symbol), side(side), order_type(order_type), quantity(qty), price(px), time_in_force(time_in_force) {}

    // for Limit order
    Order(const std::string& symbol, const double qty, const OrderSide side, const OrderType order_type, const TimeInForce time_in_force)
        : symbol(symbol), side(side), order_type(order_type), quantity(qty), price(0.0), time_in_force(time_in_force) {}
};

inline FIX42::NewOrderSingle init_new_fix_order(const std::string& ticker, const double& quantity, const OrderSide& side) {
    FIX42::NewOrderSingle new_order_fix_message;

    new_order_fix_message.set(FIX::Side(FIX::Side(side == OrderSide::BUY ? FIX::Side_BUY : FIX::Side_SELL)));
    new_order_fix_message.set(FIX::TransactTime(FIX::TransactTime(true)));
    new_order_fix_message.set(FIX::Symbol(ticker));
    new_order_fix_message.set(FIX::OrderQty(quantity));

    // Account todo: add this when we need account authentication
    // if (!account.empty()) {
    //     new_order_fix_message.set(FIX::Account(account));
    // }
    return new_order_fix_message;
}

inline FIX42::NewOrderSingle init_new_fix_order(const std::string& ticker, const double& quantity, const OrderSide& side, const std::string& custom_order_id) {
    FIX42::NewOrderSingle new_order_fix_message = init_new_fix_order(ticker, quantity, side);
    new_order_fix_message.set(FIX::ClOrdID(custom_order_id));

    return new_order_fix_message;
}

#endif //ELSA_FYP_CLIENT_SDK_ORDER_H