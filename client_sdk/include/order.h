#ifndef ELSA_FYP_CLIENT_SDK_ORDER_H
#define ELSA_FYP_CLIENT_SDK_ORDER_H

#include <string>

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

#endif //ELSA_FYP_CLIENT_SDK_ORDER_H