#pragma once

#include <map>
#include <deque>
#include "order.hpp"
#include "order_location.hpp"

using IndexIterator = std::map<uint16_t, OrderLocation>::iterator;

class OrderBook {
private:
    std::map<uint64_t, std::list<Order>> asks; // sell orders
    std::map<uint64_t, std::list<Order>, std::greater<>> bids; // buy orders
    std::map<uint16_t, OrderLocation> index;

public:
    OrderBook(/* args */);
    ~OrderBook();

    void match_order(Order order);
    bool cancel_order(uint16_t orderId);
    bool modify_quantity(uint16_t orderId, uint32_t quantity);
    bool modify_price(uint16_t orderId, uint64_t price);

    void print_bids();
    void print_asks();

    // helpers
    bool empty() const;
    bool has_order(uint16_t orderId) const;

private:
    Order match_buy(Order order);
    Order match_sell(Order order);

    void insert(Order order);
    void cancel_by_iterator(IndexIterator it);
};
