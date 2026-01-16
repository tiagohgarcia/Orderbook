#include "OrderBook.hpp"

OrderBook::OrderBook(/* args */)
{
}

OrderBook::~OrderBook()
{
}

void OrderBook::storeOrder(Order order)
{
    if(order.side == BUY) {
        asks[order.price] = order;
    }
    else if(order.side == SELL) {
        bids[order.price] = order;
    }
}