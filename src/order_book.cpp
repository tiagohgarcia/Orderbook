#include <iostream>
#include <cassert>
#include "order_book.hpp"

OrderBook::OrderBook(/* args */) {
}

OrderBook::~OrderBook() {
    for(auto& [price, level] : asks) {
        while(!level.empty()) {
            delete level.pop_front();
        }
    }

    for(auto& [price, level] : bids) {
        while(!level.empty()) {
            delete level.pop_front();
        }
    }

    index.clear();
    asks.clear();
    bids.clear();
}

void OrderBook::match_order(Order order) {
    //std::cout << "Match " << order.side << " order: " << order.id << " qty: " << order.quantity << " price: " << order.price << std::endl;
    if(order.side == BUY) {
        order = match_buy(order);
    }
    else if(order.side == SELL) {
        order = match_sell(order);
    }

    if(order.quantity > 0)
    {
        //std::cout << "Insert order: " << order.id << " qty: " << order.quantity << " price: " << order.price << std::endl;
        insert(order);
    }
}

bool OrderBook::cancel_order(uint16_t orderId) {
    auto it = index.find(orderId);
    if(it == index.end()) return false; // order id does not exist
    
    cancel_by_iterator(it);

    return true;
}

void OrderBook::cancel_by_iterator(IndexIterator it) {
    OrderLocation& location =  it->second;
    Order* doomed = location.order;

    if(location.side == BUY) {
        auto it_side = bids.find(location.price); // get iterator for element in map
        assert(it_side != bids.end()); // assert it exists
        
        it_side->second.remove(doomed); // delete from Order list
        if(it_side->second.empty()) // if list becomes empty
        {
            bids.erase(it_side); // delete price level from map
        }
    }
    else if(location.side == SELL) {
        auto it_side = asks.find(location.price);
        assert(it_side != asks.end());

        it_side->second.remove(doomed);
        if(it_side->second.empty())
        {
            asks.erase(it_side);
        }
    }

    index.erase(it);
    delete doomed;
}

bool OrderBook::modify_quantity(uint16_t orderId, uint32_t quantity) {
    if(quantity == 0) return false;
    
    auto it = index.find(orderId);
    if(it == index.end()) return false; // order id does not exist

    OrderLocation& location =  it->second;
    uint64_t price = location.price;
    Side side = location.side;

    cancel_by_iterator(it); // call cancel order to delete it from the book

    Order order = {
        orderId,
        side,
        price,
        quantity
    };

    match_order(order);

    return true;
}

bool OrderBook::modify_price(uint16_t orderId, uint64_t price) {
    if(price == 0) return false;

    auto it = index.find(orderId);
    if(it == index.end()) return false;

    OrderLocation& location =  it->second;
    Side side = location.side;
    uint32_t quantity = location.order->quantity;

    cancel_by_iterator(it);

    Order order = {
        orderId,
        side,
        price,
        quantity
    };

    match_order(order);

    return true;
}

void OrderBook::insert(Order order) {
    
    Order* new_order = new Order(order);
    
    if(new_order->side == BUY) {
        // insert in book map
        bids[new_order->price].push_back(new_order);

        // insert in index map
        index[new_order->id] = OrderLocation {
            new_order->side,
            new_order->price,
            new_order
        };
    }
    else if (new_order->side == SELL) {
        // insert in book map
        asks[new_order->price].push_back(new_order);

        // insert in index map
        index[new_order->id] = OrderLocation {
            new_order->side,
            new_order->price,
            new_order
        };
    }
}

Order OrderBook::match_buy(Order order) {
    while(!asks.empty() && order.quantity > 0)
    {
        auto it = asks.begin();

        if(it->first > order.price) { // if no ask that matches the bid
            break;
        }

        auto& level = it->second;
        Order* current = level.front();
        assert(current != nullptr);

        uint32_t match_qty = std::min(order.quantity, current->quantity);

        order.quantity -= match_qty;
        current->quantity -= match_qty;

        if(current->quantity == 0) { // ask order quantity == 0, then remove it from list
            Order* removed = level.pop_front();
            assert(removed == current);

            index.erase(removed->id);
            
            delete removed;
            
            if(level.empty())
            {
                asks.erase(it); // erase price from asks map
            }
        }
    }
    return order;
}

Order OrderBook::match_sell(Order order) {
    while(!bids.empty() && order.quantity > 0)
    {
        auto it = bids.begin();

        if(it->first < order.price) { // if no bid that matches the ask
            break;
        }

        auto& level = it->second;
        Order* current = level.front();
        assert(current != nullptr);

        uint32_t match_qty = std::min(order.quantity, current->quantity);

        order.quantity -= match_qty;
        current->quantity -= match_qty;

        if(current->quantity == 0) { // bid order quantity == 0, then remove it from list
            Order* removed = level.pop_front();
            assert(removed == current);

            index.erase(removed->id);
            
            delete removed;

            if(level.empty())
            {
                bids.erase(it); // erase price from bids map
            }
        }
    }
    return order;
}

void OrderBook::print_bids() {
//     std::cout << "\n---- BIDS ----\n" << std::endl;
//     std::cout << "Price  |  Quantity" << std::endl;
//     std::cout << "-------|----------" << std::endl;

//     for(const auto& [price,orders] : bids)
//     {
//         uint32_t qty = 0;
//         for(const Order& order : orders) {
//             qty += order.quantity;
//         }

//         std::cout << price << "   |  " << qty << std::endl;
//     }
}

void OrderBook::print_asks() {
    // std::cout << "\n---- ASKS ----\n" << std::endl;
    // std::cout << "Price  |  Quantity" << std::endl;
    // std::cout << "-------|----------" << std::endl;
    // for(const auto& [price,orders] : asks)
    // {
    //     uint32_t qty = 0;
    //     for(const Order& order : orders) {
    //         qty += order.quantity;
    //     }

    //     std::cout << price << "   |  " << qty << std::endl;
    // }
}

bool OrderBook::empty() const {
    if(bids.empty() && asks.empty()) return true;

    return false;
}

bool OrderBook::has_order(uint16_t orderId) const {
    if(index.find(orderId) != index.end()) return true;

    return false;
}