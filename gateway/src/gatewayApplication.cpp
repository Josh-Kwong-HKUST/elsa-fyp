#include "quickfix/config.h"

#include "gatewayApplication.h"
#include "quickfix/Session.h"

#include "quickfix/fix42/ExecutionReport.h"

void Application::onLogon(const FIX::SessionID &sessionID) {}

void Application::onLogout(const FIX::SessionID &sessionID) {}

void Application::fromApp(const FIX::Message &message, const FIX::SessionID &sessionID)
    EXCEPT(FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType)
{
    crack(message, sessionID);
}

void Application::onMessage(const FIX42::NewOrderSingle &message, const FIX::SessionID &)
{
    FIX::SenderCompID senderCompID;
    FIX::TargetCompID targetCompID;
    FIX::ClOrdID clOrdID;
    FIX::Symbol symbol;
    FIX::Side side;
    FIX::OrdType ordType;
    FIX::Price price;
    FIX::OrderQty orderQty;
    FIX::TimeInForce timeInForce(FIX::TimeInForce_DAY);

    message.getHeader().get(senderCompID);
    message.getHeader().get(targetCompID);
    message.get(clOrdID);
    message.get(symbol);
    message.get(side);
    message.get(ordType);
    message.get(price);
    message.get(orderQty);
    message.getFieldIfSet(timeInForce);

    try
    {
        if (timeInForce != FIX::TimeInForce_DAY)
        {
            throw std::logic_error("Unsupported TIF, use Day");
        }

        // TODO: Requires type conversion handling here. The fields are double in FIX.
        // For simplicity, we are using int in the internal Order representation.
        Order order{std::stoi(clOrdID), price, orderQty, convert(side)};
        processOrder(order);
    }
    catch (std::exception &e)
    {
        rejectOrder(senderCompID, targetCompID, clOrdID, symbol, side, e.what());
    }
}

void Application::onMessage(const FIX42::OrderCancelRequest &message, const FIX::SessionID &)
{
    FIX::OrigClOrdID origClOrdID;
    FIX::Symbol symbol;
    FIX::Side side;

    message.get(origClOrdID);
    message.get(symbol);
    message.get(side);

    try
    {
        processCancel(std::stoi(origClOrdID), symbol, convert(side));
    }
    catch (std::exception &)
    {
    }
}

void Application::updateOrder(const Order &order, char status)
{
    FIX::TargetCompID targetCompID("CLIENT_1"); // TODO: Hard code COMP ids for now
    FIX::SenderCompID senderCompID("SERVER");

    FIX42::ExecutionReport fixOrder(
        FIX::OrderID(std::to_string(order.get_order_id())),
        FIX::ExecID(idGenerator.genExecutionID()),
        FIX::ExecTransType(FIX::ExecTransType_NEW),
        FIX::ExecType(status),
        FIX::OrdStatus(status),
        FIX::Symbol("test_ticker"), // TODO: Hard code symbol for now
        FIX::Side(convert(order.get_side())),
        FIX::LeavesQty(order.get_quantity()),
        FIX::CumQty(0),
        FIX::AvgPx(0));

    fixOrder.set(FIX::ClOrdID(std::to_string(order.get_order_id())));
    fixOrder.set(FIX::OrderQty(order.get_quantity()));

    try
    {
        FIX::Session::sendToTarget(fixOrder, senderCompID, targetCompID);
    }
    catch (FIX::SessionNotFound &)
    {
    }
}

void Application::rejectOrder(
    const FIX::SenderCompID &sender,
    const FIX::TargetCompID &target,
    const FIX::ClOrdID &clOrdID,
    const FIX::Symbol &symbol,
    const FIX::Side &side,
    const std::string &message)
{
    FIX::TargetCompID targetCompID(sender.getValue());
    FIX::SenderCompID senderCompID(target.getValue());

    FIX42::ExecutionReport fixOrder(
        FIX::OrderID(clOrdID.getValue()),
        FIX::ExecID(idGenerator.genExecutionID()),
        FIX::ExecTransType(FIX::ExecTransType_NEW),
        FIX::ExecType(FIX::ExecType_REJECTED),
        FIX::OrdStatus(FIX::ExecType_REJECTED),
        symbol,
        side,
        FIX::LeavesQty(0),
        FIX::CumQty(0),
        FIX::AvgPx(0));

    fixOrder.set(clOrdID);
    fixOrder.set(FIX::Text(message));

    try
    {
        FIX::Session::sendToTarget(fixOrder, senderCompID, targetCompID);
    }
    catch (FIX::SessionNotFound &)
    {
    }
}

void Application::processOrder(const Order &order)
{

    auto result{limitOrderBook.add_order(order.get_order_id(), order.get_price(), order.get_quantity(), order.get_side())};

    if (!result.has_value())
    {
        rejectOrder(order);
        return;
    }
}

void Application::processCancel(int orderId, const std::string &symbol, Side side)
{
    auto result {limitOrderBook.cancel_order(orderId)};
    
}

Side Application::convert(const FIX::Side &side)
{
    switch (side)
    {
    case FIX::Side_BUY:
        return Side::Bid;
    case FIX::Side_SELL:
        return Side::Ask;
    default:
        throw std::logic_error("Unsupported Side, use buy or sell");
    }
}

FIX::Side Application::convert(Side side)
{
    switch (side)
    {
    case Side::Bid:
        return FIX::Side(FIX::Side_BUY);
    case Side::Ask:
        return FIX::Side(FIX::Side_SELL);
    default:
        throw std::logic_error("Unsupported Side, use buy or sell");
    }
}