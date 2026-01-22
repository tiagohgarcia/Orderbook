#pragma once

#include <map>
#include <deque>
#include "Order.hpp"
#include "OrderLocation.hpp"

class OrderBook
{
private:
    std::map<uint64_t, std::list<Order>> asks; // sell orders
    std::map<uint64_t, std::list<Order>, std::greater<>> bids; // buy orders
    std::map<uint16_t, OrderLocation> index;
public:
    OrderBook(/* args */);
    ~OrderBook();

    void matchOrder(Order order);

    void printBids();
    void printAsks();

private:
    Order matchBuy(Order order);
    Order matchSell(Order order);

    void insert(Order order);
};
