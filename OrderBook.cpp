#include <iostream>
#include "OrderBook.hpp"

OrderBook::OrderBook(/* args */)
{
}

OrderBook::~OrderBook()
{
}

void OrderBook::storeOrder(Order order)
{
    order = matchOrder(order);
    if(order.quantity <= 0) return;

    if(order.side == BUY) {
        bids[order.price].push_back(order);
    }
    else if(order.side == SELL) {
        asks[order.price].push_back(order);
    }
}

Order OrderBook::matchOrder(Order order)
{
    if(order.side == BUY) {
        while(!asks.empty() && order.quantity > 0)
        {
            auto it = asks.begin();

            if(it->first > order.price) { // if no ask that matches the bid
                break;
            }

            auto& queue = it->second;
            Order& current = queue.front();

            uint32_t match_qty = std::min(order.quantity, current.quantity);

            order.quantity -= match_qty;
            current.quantity -= match_qty;

            if(current.quantity == 0) { // ask order quantity == 0, then remove it from queue
                queue.pop_front();
                if(queue.empty())
                {
                    asks.erase(it); // erase price from asks map
                }
            }
        }
    }
    else if(order.side == SELL) {
        while(!bids.empty() && order.quantity > 0)
        {
            auto it = bids.begin();

            if(it->first < order.price || order.quantity == 0) { // if no bid that matches the ask
                break;
            }

            auto& queue = it->second;
            Order& current = queue.front();

            uint32_t match_qty = std::min(order.quantity, current.quantity);

            order.quantity -= match_qty;
            current.quantity -= match_qty;

            if(current.quantity == 0) { // bid order quantity == 0, then remove it from queue
                queue.pop_front();
                if(queue.empty())
                {
                    bids.erase(it); // erase price from bids map
                }
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