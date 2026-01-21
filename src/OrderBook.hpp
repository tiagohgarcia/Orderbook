#include "Order.hpp"
#include <map>
#include <deque>

class OrderBook
{
private:
    std::map<uint64_t, std::list<Order>> asks; // sell orders
    std::map<uint64_t, std::list<Order>, std::greater<>> bids; // buy orders
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
