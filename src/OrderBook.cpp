#include <iostream>
#include <cassert>
#include "OrderBook.hpp"

OrderBook::OrderBook(/* args */) {
}

OrderBook::~OrderBook() {
}

void OrderBook::matchOrder(Order order) {
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

bool OrderBook::cancelOrder(uint16_t orderId) {
    auto it = index.find(orderId);
    if(it == index.end()) return false; // order id does not exist
    
    cancelByIterator(it);

    return true;
}

void OrderBook::cancelByIterator(IndexIterator it) {
    OrderLocation& location =  it->second;
    if(location.side == BUY) {
        auto itSide = bids.find(location.price); // get iterator for element in map
        assert(itSide != bids.end()); // assert it exists
        
        itSide->second.erase(location.it); // delete from Order list
        if(itSide->second.empty()) // if list becomes empty
        {
            bids.erase(itSide); // delete price level from map
        }
    }
    else if(location.side == SELL) {
        auto itSide = asks.find(location.price);
        assert(itSide != asks.end());

        itSide->second.erase(location.it);
        if(itSide->second.empty())
        {
            asks.erase(itSide);
        }
    }

    index.erase(it);
}

bool OrderBook::modifyQuantity(uint16_t orderId, uint32_t quantity) {
    if(quantity == 0) return false;
    
    auto it = index.find(orderId);
    if(it == index.end()) return false; // order id does not exist

    OrderLocation& location =  it->second;
    uint64_t price = location.price;
    Side side = location.side;

    cancelByIterator(it); // call cancel order to delete it from the book

    Order order = {
        orderId,
        side,
        price,
        quantity
    };

    matchOrder(order);

    return true;
}

void OrderBook::insert(Order order) {
    if(order.side == BUY) {
        // insert in book map
        auto it = bids[order.price].insert(
            bids[order.price].end(), 
            order);

        // insert in index map
        index[order.id] = OrderLocation {
            order.side,
            order.price,
            it
        };
    }
    else if (order.side == SELL) {
        // insert in book map
        auto it = asks[order.price].insert(
            asks[order.price].end(), 
            order);

        // insert in index map
        index[order.id] = OrderLocation {
            order.side,
            order.price,
            it
        };
    }
}

Order OrderBook::matchBuy(Order order) {
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
            auto itIndex = index.find(current.id); // remove id from index map
            assert(itIndex != index.end());
            index.erase(itIndex);
            
            list.pop_front();
            if(list.empty())
            {
                asks.erase(it); // erase price from asks map
            }
        }
    }
    return order;
}

Order OrderBook::matchSell(Order order) {
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
            auto itIndex = index.find(current.id); // remove id from index map
            assert(itIndex != index.end());
            index.erase(itIndex);
            
            list.pop_front();
            if(list.empty())
            {
                bids.erase(it); // erase price from bids map
            }
        }
    }
    return order;
}

void OrderBook::printBids() {
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

void OrderBook::printAsks() {
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

bool OrderBook::empty() const {
    if(bids.empty() && asks.empty()) return true;

    return false;
}

bool OrderBook::hasOrder(uint16_t orderId) const {
    if(index.find(orderId) != index.end()) return true;

    return false;
}