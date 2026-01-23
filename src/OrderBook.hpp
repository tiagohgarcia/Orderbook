#pragma once

#include <map>
#include <deque>
#include "Order.hpp"
#include "OrderLocation.hpp"

using IndexIterator = std::map<uint16_t, OrderLocation>::iterator;

class OrderBook {
private:
    std::map<uint64_t, std::list<Order>> asks; // sell orders
    std::map<uint64_t, std::list<Order>, std::greater<>> bids; // buy orders
    std::map<uint16_t, OrderLocation> index;

public:
    OrderBook(/* args */);
    ~OrderBook();

    void matchOrder(Order order);
    bool cancelOrder(uint16_t orderId);
    bool modifyQuantity(uint16_t orderId, uint32_t quantity);
    bool modifyPrice(uint16_t orderId, uint64_t price);

    void printBids();
    void printAsks();

    // helpers
    bool empty() const;
    bool hasOrder(uint16_t orderId) const;

private:
    Order matchBuy(Order order);
    Order matchSell(Order order);

    void insert(Order order);
    void cancelByIterator(IndexIterator it);
};
