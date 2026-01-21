#include <iostream>
#include "OrderBook.hpp"

OrderBook::OrderBook(/* args */)
{
}

OrderBook::~OrderBook()
{
}

void OrderBook::matchOrder(Order order)
{
    //std::cout << "Match " << order.side << " order: " << order.id << " qty: " << order.quantity << " price: " << order.price << std::endl;
    if(order.side == BUY) {
        order = matchBuy(order);
    }
    else if(order.side == SELL) {
        order = matchSell(order);
    }

    if(order.quantity > 0)
    {
        //std::cout << "Insert order: " << order.id << " qty: " << order.quantity << " price: " << order.price << std::endl;
        insert(order);
    }
}

void OrderBook::insert(Order order)
{
    if(order.side == BUY) {
        bids[order.price].push_back(order);
    }
    else if(order.side == SELL) {
        asks[order.price].push_back(order);
    }
}

Order OrderBook::matchBuy(Order order)
{
    while(!asks.empty() && order.quantity > 0)
    {
        auto it = asks.begin();

        if(it->first > order.price) { // if no ask that matches the bid
            break;
        }

        auto& list = it->second;
        Order& current = list.front();

        uint32_t match_qty = std::min(order.quantity, current.quantity);

        order.quantity -= match_qty;
        current.quantity -= match_qty;

        if(current.quantity == 0) { // ask order quantity == 0, then remove it from list
            list.pop_front();
            if(list.empty())
            {
                asks.erase(it); // erase price from asks map
            }
        }
    }
    return order;
}

Order OrderBook::matchSell(Order order)
{
    while(!bids.empty() && order.quantity > 0)
    {
        auto it = bids.begin();

        if(it->first < order.price) { // if no bid that matches the ask
            break;
        }

        auto& list = it->second;
        Order& current = list.front();

        uint32_t match_qty = std::min(order.quantity, current.quantity);

        order.quantity -= match_qty;
        current.quantity -= match_qty;

        if(current.quantity == 0) { // bid order quantity == 0, then remove it from list
            list.pop_front();
            if(list.empty())
            {
                bids.erase(it); // erase price from bids map
            }
        }
    }
    return order;
}

void OrderBook::printBids()
{
    std::cout << "\n---- BIDS ----\n" << std::endl;
    std::cout << "Price  |  Quantity" << std::endl;
    std::cout << "-------|----------" << std::endl;

    for(const auto& [price,orders] : bids)
    {
        uint32_t qty = 0;
        for(const Order& order : orders) {
            qty += order.quantity;
        }

        std::cout << price << "   |  " << qty << std::endl;
    }
}

void OrderBook::printAsks()
{
    std::cout << "\n---- ASKS ----\n" << std::endl;
    std::cout << "Price  |  Quantity" << std::endl;
    std::cout << "-------|----------" << std::endl;
    for(const auto& [price,orders] : asks)
    {
        uint32_t qty = 0;
        for(const Order& order : orders) {
            qty += order.quantity;
        }

        std::cout << price << "   |  " << qty << std::endl;
    }
}